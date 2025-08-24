#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ALSS Dashboard Builder (solved.ac only)
- Update each week's README tables (O/X: PRE/DURING/NONE)
- Update root README's 3 blocks: WEEKS, LEADERBOARD, TREND
"""

import os, re, time, math, json, sys
from datetime import datetime, timezone
from typing import Dict, List, Set, Tuple
import requests
import yaml

ROOT_DIR = os.path.dirname(os.path.dirname(__file__))
CONFIG_DIR = os.path.join(ROOT_DIR, "config")

PARTICIPANTS_YAML = os.path.join(CONFIG_DIR, "participants.yaml")
WEEKS_YAML = os.path.join(CONFIG_DIR, "weeks.yaml")
ROOT_README = os.path.join(ROOT_DIR, "README.md")

# ---------- solved.ac API ----------
SOLVED_BASE = "https://solved.ac/api/v3"
SESSION = requests.Session()
SESSION.headers.update({
    "User-Agent": "alss-dashboard/1.0 (+https://github.com/your/repo)",
    # solved.ac는 보통 키가 없어도 호출 가능. 필요 시 헤더/쿼리 추가
})

def _get(url, params=None, max_retry=5):
    for i in range(max_retry):
        r = SESSION.get(url, params=params, timeout=30)
        if r.status_code == 429:
            retry_after = int(r.headers.get("Retry-After", "3"))
            time.sleep(max(3, retry_after))
            continue
        r.raise_for_status()
        # rate limit 보호용 소폭 지연
        time.sleep(0.25)
        return r.json()
    raise RuntimeError(f"Too many 429s for {url} {params}")

def solved_search_problem(query: str, page: int = 1) -> dict:
    return _get(f"{SOLVED_BASE}/search/problem", params={"query": query, "page": page})

def solved_problem_lookup(pids: List[int]) -> Dict[int, dict]:
    """문제 메타(티어 등). 최대 100개 정도까지 분할 호출."""
    meta: Dict[int, dict] = {}
    BATCH = 80
    for i in range(0, len(pids), BATCH):
        chunk = pids[i:i+BATCH]
        data = _get(f"{SOLVED_BASE}/problem/lookup", params={"problemIds": ",".join(map(str, chunk))})
        for item in data:
            meta[item["problemId"]] = item
    return meta

# ---------- 데이터 모델 ----------
def load_yaml(path: str):
    with open(path, "r", encoding="utf-8") as f:
        return yaml.safe_load(f)

def read_file(path: str) -> str:
    with open(path, "r", encoding="utf-8") as f:
        return f.read()

def write_if_changed(path: str, new_text: str) -> bool:
    old = read_file(path) if os.path.exists(path) else ""
    if old != new_text:
        with open(path, "w", encoding="utf-8") as f:
            f.write(new_text)
        return True
    return False

# ---------- 집계 로직 ----------
def parse_iso(s: str) -> datetime:
    # 2025-08-21T00:00:00+09:00 → aware dt
    return datetime.fromisoformat(s)

def solved_set(handle: str, after: str = None, before: str = None, restrict_ids: Set[int] = None) -> Set[int]:
    """
    solved.ac 검색으로 '해결한 문제 집합'을 받아온다.
    - query: solved_by:<handle> + 기간 필터
    - ID 필터는 client-side 교집합으로 처리 (안정성 확보)
    """
    q = [f"solved_by:{handle}"]
    if after:
        q.append(f"solved_after:{after[:10]}")   # YYYY-MM-DD
    if before:
        q.append(f"solved_before:{before[:10]}")
    query = " ".join(q)

    got: Set[int] = set()
    page = 1
    while True:
        data = solved_search_problem(query, page=page)
        for it in data.get("items", []):
            pid = it["problemId"]
            if restrict_ids is None or pid in restrict_ids:
                got.add(pid)
        count = data.get("count", 0)
        total_pages = max(1, math.ceil(count / 50))
        if page >= total_pages or len(data.get("items", [])) == 0:
            break
        page += 1
    return got

def classify_states(week_cfg, members, group_key, problems: List[int]) -> Dict[int, Dict[str, str]]:
    """
    문제ID -> { seat# -> 'PRE'|'DURING'|'NONE' }
    PRE : released_at 이전에 풂
    DURING : released_at 이후(마감 제한 없음) 풂
    """
    released_at = week_cfg["released_at"]  # ISO8601
    #마감 제한 두고 싶으면 weeks.yaml에 deadline 추가 후 here에서 before=deadline 넘기기
    results: Dict[int, Dict[str, str]] = {pid: {} for pid in problems}

    pset = set(problems)

    for m in members:
        seat = str(m["seat"])
        handle = m["solved_handle"]

        pre = solved_set(handle, before=released_at, restrict_ids=pset)
        during = solved_set(handle, after=released_at, restrict_ids=pset)

        for pid in problems:
            if pid in pre:
                results[pid][seat] = "PRE"
            elif pid in during:
                results[pid][seat] = "DURING"
            else:
                results[pid][seat] = "NONE"
    return results

# ---------- 렌더링 ----------
def cell_for(state: str) -> str:
    return {"PRE": "☑", "DURING": "✅", "NONE": "❌"}[state]

def member_header_cells(members) -> List[str]:
    cells = []
    for m in members:
        gh = m["github"]
        seat = m["seat"]
        cells.append(f'<a href="https://github.com/{gh}" title="{gh}">#{seat}</a>')
    return cells

def build_week_table(week_cfg, group_cfg, members, problem_meta, states) -> str:
    # 헤더
    hdr = ["솔브드 티어", "번호", "제목", "링크", "폴더"] + member_header_cells(members)
    lines = [
        "| " + " | ".join(hdr) + " |",
        "|" + ":---:|" + "---:|" + ":---|" + ":---:|" + ":---:|" * (len(members)-1) + ":---:|"
    ]
    # 행
    base_dir = os.path.dirname(week_cfg["path"])
    group_title_to_dir = {
        "BEGINNER": "브루트포스&재귀&백트래킹-초급",
        "ADVANCED": "브루트포스&재귀&백트래킹-고급",
        "DNC": "분할정복",
    }
    group_dir = group_title_to_dir.get(group_cfg["key"], "")

    for pid in group_cfg["problems"]:
        meta = problem_meta.get(pid, {})
        tier = meta.get("level", 0)  # 1..31
        title = meta.get("titleKo", "") or meta.get("title", "")
        tier_img = f'<img src="https://static.solved.ac/tier_small/{tier}.svg" alt="{tier}" width="20"/>'
        link = f"[🔗](https://www.acmicpc.net/problem/{pid})"
        folder = f"[📁]({os.path.join('.', group_dir, f'boj_{pid}_{safe_slug(title)}').replace(' ', '_')})"

        row = [tier_img, str(pid), title, link, folder]
        for m in members:
            seat = str(m["seat"])
            row.append(cell_for(states[pid][seat]))
        lines.append("| " + " | ".join(row) + " |")
    return "\n".join(lines)

def safe_slug(s: str) -> str:
    return re.sub(r"[^\w가-힣\-\(\)_]+", "_", s)

def replace_block(text: str, marker: str, new_md: str) -> str:
    start = f"<!--START:{marker}-->"
    end   = f"<!--END:{marker}-->"
    pat = re.compile(re.escape(start) + r".*?" + re.escape(end), flags=re.DOTALL)
    rep = f"{start}\n\n{new_md}\n\n{end}"
    if pat.search(text):
        return pat.sub(rep, text)
    # 없는 경우 맨 아래에 추가
    return text.strip() + "\n\n" + rep + "\n"

def render_week_readme(week_cfg, participants, problem_meta_by_group, states_by_group):
    path = os.path.join(ROOT_DIR, week_cfg["path"])
    text = read_file(path)
    for g in week_cfg["groups"]:
        marker = f"PROGRESS:{g['key']}"
        table_md = build_week_table(week_cfg, g, participants, problem_meta_by_group[g["key"]], states_by_group[g["key"]])
        text = replace_block(text, marker, table_md)
    changed = write_if_changed(path, text)
    return changed

# ---------- 루트 README 대시보드 ----------
def render_root_dashboards(root_readme_path: str, participants, weeks_cfg, states_bundle):
    # 주차별 완료율 (%), 리더보드, 누적 추세
    # 1) 준비: 각 주차별 문제 세트, 멤버별 해결 set
    week_sets: List[Set[int]] = []
    week_titles: List[str] = []
    solved_by_member_per_week: List[Dict[str, Set[int]]] = []

    for w in weeks_cfg:
        pids = set()
        for g in w["groups"]:
            pids.update(g["problems"])
        week_sets.append(pids)
        week_titles.append(f"{int(w['id']):02d}")

        solved_map: Dict[str, Set[int]] = {}
        for m in participants:
            seat = str(m["seat"])
            solved = set()
            for g in w["groups"]:
                for pid, seat_states in states_bundle[w["id"]][g["key"]].items():
                    if seat_states[seat] in ("PRE", "DURING"):
                        solved.add(pid)
            solved_map[seat] = solved
        solved_by_member_per_week.append(solved_map)

    # 2) 주차별 완료율 (%): 행=주차, 열=멤버, 마지막 열 합계(%)
    def week_matrix_md():
        header = ["주차＼멤버"] + [m["name"] for m in participants] + ["합계(%)"]
        lines = ["| " + " | ".join(header) + " |",
                 "|" + "---|" * (len(header)-1) + "---|"]
        col_tot_solved = [0]*len(participants)
        col_tot_assign = [0]*len(participants)

        for widx, wk in enumerate(week_sets):
            assign = len(wk)
            row = [week_titles[widx]]
            row_sum_solved = 0
            for mi, m in enumerate(participants):
                seat = str(m["seat"])
                solved = len(solved_by_member_per_week[widx][seat] & wk)
                row_sum_solved += solved
                col_tot_solved[mi] += solved
                col_tot_assign[mi] += assign
                rate = round(solved / assign * 100) if assign else 0
                row.append(str(rate))
            row.append(str(round(row_sum_solved / (assign*len(participants)) * 100) if assign else 0))
            lines.append("| " + " | ".join(row) + " |")

        # 합계(%) 행
        total_row = ["합계(%)"]
        for mi in range(len(participants)):
            rate = round(col_tot_solved[mi] / col_tot_assign[mi] * 100) if col_tot_assign[mi] else 0
            total_row.append(str(rate))
        # 전체 평균
        overall_rate = round(sum(col_tot_solved) / (sum(col_tot_assign)) * 100) if sum(col_tot_assign) else 0
        total_row.append(str(overall_rate))
        lines.append("| " + " | ".join(total_row) + " |")
        return "\n".join(lines)

    # 3) 리더보드 (누적)
    def leaderboard_md():
        assigned_total = sum(len(ws) for ws in week_sets)
        scores = []
        for m in participants:
            seat = str(m["seat"])
            solved = 0
            for widx, ws in enumerate(week_sets):
                solved += len(solved_by_member_per_week[widx][seat] & ws)
            scores.append((m["name"], solved))
        scores.sort(key=lambda x: x[1], reverse=True)
        lines = ["### 전체 리더보드 (누적)"]
        for i, (name, sc) in enumerate(scores, 1):
            rate = round(sc / assigned_total * 100) if assigned_total else 0
            lines.append(f"{i}) {name} — **{sc}/{assigned_total} ({rate}%)**")
        return "\n".join(lines)

    # 4) 멤버별 주차별 누적 추세
    def trend_md():
        # 누적 유니크 집합
        cum_sets = []
        acc = set()
        for ws in week_sets:
            acc = acc | ws
            cum_sets.append(set(acc))

        header = ["주차＼멤버"] + [m["name"] for m in participants]
        lines = ["| " + " | ".join(header) + " |",
                 "|" + "---|" * (len(header)-1) + "---|"]

        for k, U in enumerate(cum_sets):
            row = [week_titles[k]]
            denom = len(U)
            for m in participants:
                seat = str(m["seat"])
                solved = 0
                for j in range(k+1):
                    solved += len(solved_by_member_per_week[j][seat] & week_sets[j])
                rate = round(solved / denom * 100) if denom else 0
                row.append(f"{solved}/{denom} ({rate})")
            lines.append("| " + " | ".join(row) + " |")
        return "\n".join(["### 멤버별 주차별 누적 추세 (누적 해결 / 누적 배정, %)"] + lines)

    text = read_file(root_readme_path)
    def rep(marker, md):
        return replace_block(text, marker, md)

    text = replace_block(text, "DASHBOARD_WEEKS", "\n".join(["### 주차별 완료율 (%)", week_matrix_md()]))
    text = replace_block(text, "DASHBOARD_LEADERBOARD", leaderboard_md())
    text = replace_block(text, "DASHBOARD_TREND", trend_md())
    changed = write_if_changed(root_readme_path, text)
    return changed

# ---------- 엔트리 ----------
def main():
    participants = load_yaml(PARTICIPANTS_YAML)["members"]
    weeks_cfg = load_yaml(WEEKS_YAML)["weeks"]

    # 멤버 seat 순 정렬 보장
    participants = sorted(participants, key=lambda m: m["seat"])

    # 주별 계산 + 표 갱신
    # 그룹별 문제 메타/상태 캐싱
    states_bundle = {}  # week_id -> group_key -> {pid -> {seat -> state}}
    for w in weeks_cfg:
        states_bundle[w["id"]] = {}
        all_pids = []
        for g in w["groups"]:
            all_pids.extend(g["problems"])
        meta = solved_problem_lookup(sorted(set(all_pids)))

        problem_meta_by_group = {}
        states_by_group = {}
        for g in w["groups"]:
            problem_meta_by_group[g["key"]] = {pid: meta.get(pid, {}) for pid in g["problems"]}
            states = classify_states(w, participants, g["key"], g["problems"])
            states_by_group[g["key"]] = states
        # 주차 README 갱신
        render_week_readme(w, participants, problem_meta_by_group, states_by_group)
        states_bundle[w["id"]] = states_by_group

    # 루트 README 갱신
    render_root_dashboards(ROOT_README, participants, weeks_cfg, states_bundle)

if __name__ == "__main__":
    main()
