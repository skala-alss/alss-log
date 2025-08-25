#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ALSS Dashboard Builder (solved.ac + Git repo)
- Week README: ONLY update member columns (#1..#N)
  DURING: solved_by & repo(main or any branch) has member file
  PRE   : solved_by & no member file in repo
  NONE  : not solved_by
  * Old filename rule supported: week root: boj_{pid}_{member}.ext
- Root README:
  1) 주차별 완료율(배정세트 기준, PRE/DURING=해결)
  2) 전체 리더보드(동일)
  3) 멤버별 주차별 누적 추세(제출 주차 귀속: squash merge 커밋 제목 → 브랜치명)

Env:
  ALSS_OVERWRITE=1        # overwrite all member cells (default: fill blanks only)
  ALSS_CHECK_BRANCHES=1   # scan all refs/heads + refs/remotes (default: 1)
  ALSS_DEBUG=1            # debug logs
"""

import os, re, time, math, subprocess, shlex
from typing import Dict, List, Set, Tuple
import requests, yaml

# ---------- Paths ----------
ROOT_DIR = os.path.dirname(os.path.dirname(__file__))
CONFIG_DIR = os.path.join(ROOT_DIR, "config")

PARTICIPANTS_YAML = os.path.join(CONFIG_DIR, "participants.yaml")
WEEKS_YAML = os.path.join(CONFIG_DIR, "weeks.yaml")
ROOT_README = os.path.join(ROOT_DIR, "README.md")

# ---------- Env ----------
OVERWRITE_ALL_MEMBER_CELLS = os.getenv("ALSS_OVERWRITE", "1") == "1"
CHECK_BRANCHES = os.getenv("ALSS_CHECK_BRANCHES", "1") == "1"
DEBUG = os.getenv("ALSS_DEBUG", "1") == "1"

# ---------- solved.ac API ----------
SOLVED_BASE = "https://solved.ac/api/v3"
SESSION = requests.Session()
SESSION.headers.update({
    "User-Agent": "alss-dashboard/2.0 (+https://github.com/your/repo)",
})

def _get(url, params=None, max_retry=5):
    for _ in range(max_retry):
        r = SESSION.get(url, params=params, timeout=30)
        if r.status_code == 429:
            retry_after = int(r.headers.get("Retry-After", "3") or "3")
            time.sleep(max(3, retry_after))
            continue
        r.raise_for_status()
        time.sleep(0.25)
        return r.json()
    raise RuntimeError(f"Too many 429s for {url} {params}")

def solved_search_problem(query: str, page: int = 1) -> dict:
    return _get(f"{SOLVED_BASE}/search/problem", params={"query": query, "page": page})

def solved_set(handle: str, restrict_ids: Set[int] = None) -> Set[int]:
    """solved_by:<handle> (no date) → problemId set, restricted to given IDs."""
    q = f"solved_by:{handle}"
    got: Set[int] = set()
    page = 1
    while True:
        data = solved_search_problem(q, page=page)
        items = data.get("items", [])
        for it in items:
            pid = it["problemId"]
            if (restrict_ids is None) or (pid in restrict_ids):
                got.add(pid)
        count = data.get("count", 0)
        total_pages = max(1, math.ceil(count / 50))
        if page >= total_pages or not items:
            break
        page += 1
    return got

# ---------- IO ----------
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

# ---------- Markdown utils (patch member columns only) ----------
SYMBOL = {"PRE": "☑️", "DURING": "✅", "NONE": "❌"}

def is_blank_cell(val: str) -> bool:
    v = (val or "").strip().replace("&nbsp;", "")
    return v == ""

def _get_block(text: str, marker: str) -> Tuple[str, int, int]:
    start = f"<!--START:{marker}-->"
    end   = f"<!--END:{marker}-->"
    s = re.search(re.escape(start), text)
    e = re.search(re.escape(end), text)
    if not s or not e or s.end() >= e.start():
        return "", -1, -1
    return text[s.end():e.start()], s.start(), e.end()

def _split_row(line: str) -> List[str]:
    if not line.strip().startswith("|"):
        return []
    return [c.strip() for c in line.strip().strip("|").split("|")]

def _join_row(cells: List[str]) -> str:
    return "| " + " | ".join(cells) + " |"

def _is_separator_row(cells: List[str]) -> bool:
    return all(re.match(r"^:?-{3,}:?$", c.strip()) or c.strip() == "" for c in cells)

def patch_member_columns_in_block(block_md: str,
                                  pid_to_states: Dict[int, Dict[str, str]],
                                  participants: List[dict]) -> str:
    """표 블록(BEGINNER/ADVANCED/DNC)에서 멤버 열만 갱신."""
    lines = block_md.strip("\n").splitlines()
    if len(lines) < 2:
        return block_md

    # 헤더 찾기
    header_idx = None
    for i, ln in enumerate(lines):
        if ln.strip().startswith("|"):
            header_idx = i
            break
    if header_idx is None or header_idx + 1 >= len(lines):
        return block_md

    header = _split_row(lines[header_idx])
    try:
        folder_col = header.index("폴더")
        number_col = header.index("번호")
    except ValueError:
        return block_md  # 예상 헤더와 다르면 원본 유지

    member_cols = list(range(folder_col + 1, len(header)))
    seats = [m["seat"] for m in participants]
    data_start = header_idx + 2  # header + separator

    for i in range(data_start, len(lines)):
        cells = _split_row(lines[i])
        if not cells or _is_separator_row(cells):
            continue
        # 문제 번호 파싱
        try:
            pid = int(re.sub(r"[^\d]", "", cells[number_col]))
        except ValueError:
            continue
        if pid not in pid_to_states:
            continue

        for idx, seat in enumerate(seats):
            col = member_cols[idx]
            state = pid_to_states[pid].get(str(seat), "NONE")
            if OVERWRITE_ALL_MEMBER_CELLS:
                cells[col] = SYMBOL[state]
            else:
                if is_blank_cell(cells[col]) and state != "NONE":
                    cells[col] = SYMBOL[state]
        lines[i] = _join_row(cells)

    return "\n".join(lines)

def _replace_block_exact(text: str, marker: str, new_md_inside: str, s: int, e: int) -> str:
    return text[:s] + f"<!--START:{marker}-->\n\n{new_md_inside}\n\n<!--END:{marker}-->" + text[e:]

def render_week_readme_members_only(week_cfg, participants, states_by_group):
    """주차 README의 PROGRESS 블록 내부에서 멤버 컬럼만 갱신."""
    path = os.path.join(ROOT_DIR, week_cfg["path"])
    text = read_file(path)
    changed = False

    for g in week_cfg["groups"]:
        marker = f"PROGRESS:{g['key']}"
        block, s, e = _get_block(text, marker)
        if s == -1:
            continue  # 표가 없으면 건드리지 않음
        new_block = patch_member_columns_in_block(block.strip("\n"),
                                                  states_by_group[g["key"]],
                                                  participants)
        if new_block != block.strip("\n"):
            text = _replace_block_exact(text, marker, new_block, s, e)
            changed = True

    if changed:
        write_if_changed(path, text)
    return changed

# ---------- Member / Path matching ----------
ALLOWED_EXT = {".cpp",".cc",".cxx",".c",".py",".java",".kt",".js",".ts",
               ".rb",".go",".cs",".swift",".rs",".m",".mm"}

def _norm_token(s: str) -> str:
    return re.sub(r"[\s_\-]+", "_", (s or "").strip().lower())

def _member_keys_for_match(m: dict) -> List[str]:
    keys = []
    for k in [m.get("file_key"), m.get("name"), m.get("github")]:
        if k:
            nk = _norm_token(k)
            if nk not in keys:
                keys.append(nk)
    return keys

def _split_tokens(base_noext: str) -> Set[str]:
    toks = re.split(r"[\s_\-\.]+", _norm_token(base_noext))
    return set(t for t in toks if t)

def _member_owns_path(path: str, pid: int, member: dict) -> bool:
    """
    파일이 멤버의 제출로 보이는지 판단.
    허용 패턴:
      - <...>/boj_{pid}_*/{member}[...].ext
      - <week>/boj_{pid}_{member}.ext  (옛 규칙)
    """
    base = os.path.basename(path)
    base_noext, ext = os.path.splitext(base)
    if ext.lower() not in ALLOWED_EXT:
        return False

    toks = _split_tokens(base_noext)
    keys = _member_keys_for_match(member)

    # (A) 옛 규칙: 파일명에 pid와 member 토큰이 모두 포함
    if str(pid) in toks:
        for k in keys:
            if k in toks:
                return True

    # (B) 문제폴더 내부: member 토큰이 파일명 선두/토큰에 존재
    for k in keys:
        b = base_noext.lower()
        if b == k or b.startswith(k + "_") or b.startswith(k + "-"):
            return True
        if k in toks:
            return True

    return False

# ---------- Git helpers ----------
def _run(cmd: str, cwd: str = ROOT_DIR) -> str:
    return subprocess.check_output(cmd, shell=True, cwd=cwd, text=True, stderr=subprocess.DEVNULL)

def list_all_refs() -> List[str]:
    if not CHECK_BRANCHES:
        return ["HEAD", "main", "origin/main"]
    refs = []
    try:
        out1 = _run("git for-each-ref --format='%(refname:short)' refs/heads/")
        out2 = _run("git for-each-ref --format='%(refname:short)' refs/remotes/")
        refs = [ln.strip().strip("'") for ln in (out1 + out2).splitlines() if ln.strip()]
    except Exception:
        refs = ["HEAD", "main", "origin/main"]
    # 중복 제거, main/HEAD 우선
    order = []
    seen = set()
    for r in ["HEAD", "main", "origin/main"]:
        if r not in seen:
            order.append(r); seen.add(r)
    for r in refs:
        if r not in seen:
            order.append(r); seen.add(r)
    return order

def infer_problems_root(weeks_cfg) -> str:
    # e.g. "problems/week04/README.md" -> "problems"
    for w in weeks_cfg:
        p = w.get("path", "")
        if p:
            parts = p.replace("\\","/").split("/")
            if len(parts) >= 2:
                return parts[0]
    return "problems"

def list_paths_in_ref(ref: str, rel_path: str) -> List[str]:
    try:
        cmd = f"git ls-tree -r --name-only {shlex.quote(ref)} -- {shlex.quote(rel_path)}"
        out = _run(cmd)
        return [ln.strip() for ln in out.splitlines() if ln.strip()]
    except Exception:
        return []

def paths_in_refs(refs: List[str], rel_path: str) -> List[str]:
    seen, out = set(), []
    for r in refs:
        for p in list_paths_in_ref(r, rel_path):
            if p not in seen:
                seen.add(p); out.append(p)
    return out

# ---------- Repo scanning (per week; across all branches) ----------
def collect_repo_files_for_week(week_cfg, refs: List[str]) -> Dict[int, List[str]]:
    """
    refs 각각에서 week_dir 이하 파일을 모아 pid -> [paths...] 매핑
    """
    week_dir = os.path.dirname(os.path.join(ROOT_DIR, week_cfg["path"]))  # problems/weekXX
    rel_week_dir = os.path.relpath(week_dir, ROOT_DIR).replace("\\", "/")
    paths = paths_in_refs(refs, rel_week_dir)
    by_pid: Dict[int, List[str]] = {}
    for p in paths:
        m = re.search(r"boj_(\d+)", p)
        if not m:
            continue
        pid = int(m.group(1))
        by_pid.setdefault(pid, []).append(p)
    return by_pid

# ---------- DURING/PRE classification (repo-backed) ----------
def classify_states_repo(week_cfg, members, problems: List[int]) -> Dict[int, Dict[str, str]]:
    """
    DURING: solved_by AND (repo(any ref) has member file)
    PRE   : solved_by AND (repo에 파일 없음)
    NONE  : solved_by 아님
    """
    pset = set(problems)
    results = {pid: {} for pid in problems}

    refs = list_all_refs()
    repo_index = collect_repo_files_for_week(week_cfg, refs)

    for m in members:
        seat = str(m["seat"])
        handle = m["solved_handle"]
        solved = solved_set(handle, restrict_ids=pset)
        if DEBUG:
            print(f"[debug] {handle} week={week_cfg['id']} solved={len(solved)} / assigned={len(pset)}")
        for pid in problems:
            if pid not in solved:
                results[pid][seat] = "NONE"; continue
            owned = any(_member_owns_path(path, pid, m) for path in repo_index.get(pid, []))
            results[pid][seat] = "DURING" if owned else "PRE"
    return results

# ---------- Root README dashboards ----------
def replace_block(text: str, marker: str, new_md: str) -> str:
    start = f"<!--START:{marker}-->"
    end   = f"<!--END:{marker}-->"
    pat = re.compile(re.escape(start) + r".*?" + re.escape(end), flags=re.DOTALL)
    rep = f"{start}\n\n{new_md}\n\n{end}"
    if pat.search(text):
        return pat.sub(rep, text)
    return text.strip() + "\n\n" + rep + "\n"

def wk_label(w) -> str:
    try:
        return f"{int(w['id']):02d}"
    except Exception:
        return str(w.get('id','?'))

def render_root_dashboards(root_readme_path: str, participants, weeks_cfg, states_bundle):
    # 1) 주차별 세트/타이틀
    week_sets: List[Set[int]] = []
    week_titles: List[str] = []
    solved_by_member_per_week: List[Dict[str, Set[int]]] = []

    for w in weeks_cfg:
        pids = set(pid for g in w["groups"] for pid in g["problems"])
        week_sets.append(pids)
        week_titles.append(wk_label(w))

        solved_map: Dict[str, Set[int]] = {}
        for m in participants:
            seat = str(m["seat"])
            solved = set()
            for g in w["groups"]:
                for pid, seat_states in states_bundle[w["id"]][g["key"]].items():
                    if seat_states[seat] in ("PRE","DURING"):
                        solved.add(pid)
            solved_map[seat] = solved
        solved_by_member_per_week.append(solved_map)

    # 2) 제출 주차 귀속 맵 (commit title → branch name → assignment fallback)
    submission_map = build_submission_attribution(weeks_cfg, participants)

    # 주차별 완료율 (%)
    def week_matrix_md():
        header = ["주차＼멤버"] + [m["name"] for m in participants] + ["합계(%)"]
        lines = ["| " + " | ".join(header) + " |",
                 "|" + "---|" * (len(header)-1) + "---|"]
        col_tot_solved = [0]*len(participants)
        col_tot_assign = [0]*len(participants)

        for widx, ws in enumerate(week_sets):
            assign = len(ws)
            row = [week_titles[widx]]
            row_sum = 0
            for mi, m in enumerate(participants):
                seat = str(m["seat"])
                solved = len(solved_by_member_per_week[widx][seat] & ws)
                row_sum += solved
                col_tot_solved[mi] += solved
                col_tot_assign[mi] += assign
                rate = round(solved / assign * 100) if assign else 0
                row.append(str(rate))
            row.append(str(round(row_sum / (assign*len(participants)) * 100) if assign else 0))
            lines.append("| " + " | ".join(row) + " |")

        tot = ["합계(%)"]
        for mi in range(len(participants)):
            rate = round(col_tot_solved[mi] / col_tot_assign[mi] * 100) if col_tot_assign[mi] else 0
            tot.append(str(rate))
        overall = round(sum(col_tot_solved) / sum(col_tot_assign) * 100) if sum(col_tot_assign) else 0
        tot.append(str(overall))
        lines.append("| " + " | ".join(tot) + " |")
        return "\n".join(lines)

    # 전체 리더보드
    def leaderboard_md():
        assigned_total = sum(len(ws) for ws in week_sets)
        scores = []
        for m in participants:
            seat = str(m["seat"])
            solved = sum(len(solved_by_member_per_week[widx][seat] & week_sets[widx])
                         for widx in range(len(week_sets)))
            scores.append((m["name"], solved))
        scores.sort(key=lambda x: x[1], reverse=True)
        lines = ["### 전체 리더보드 (누적)"]
        for i, (name, sc) in enumerate(scores, 1):
            rate = round(sc / assigned_total * 100) if assigned_total else 0
            lines.append(f"{i}) {name} — **{sc}/{assigned_total} ({rate}%)**")
        return "\n".join(lines)

    # 멤버별 주차별 누적 추세 (제출 주차 귀속)
    def trend_md():
        # 누적 분모: 1..k주차 배정 문제 합집합 크기
        cumulative_assign_sets: List[Set[int]] = []
        acc = set()
        for ws in week_sets:
            acc |= ws
            cumulative_assign_sets.append(set(acc))

        # 멤버별로, 제출 귀속 주차가 k 이하면 카운트
        header = ["주차＼멤버"] + [m["name"] for m in participants]
        lines = ["| " + " | ".join(header) + " |",
                 "|" + "---|" * (len(header)-1) + "---|"]

        # 편의를 위한 인덱스: 주차 라벨 → 인덱스
        week_index = {lab: i for i, lab in enumerate(week_titles)}

        for k, U in enumerate(cumulative_assign_sets):
            row = [week_titles[k]]
            denom = len(U)
            for m in participants:
                seat = str(m["seat"])
                # 제출 귀속 주차별 맵에서, 이 멤버가 제출한 (pid -> wk_label)
                mp = submission_map.get(seat, {})
                solved = sum(1 for pid, wk_lab in mp.items()
                             if pid in U and week_index.get(wk_lab, 9999) <= k)
                rate = round(solved / denom * 100) if denom else 0
                row.append(f"{solved}/{denom} ({rate})")
            lines.append("| " + " | ".join(row) + " |")

        return "\n".join(["### 멤버별 주차별 누적 추세 (제출 주차 귀속 / 배정 누적, %)"] + lines)

    text = read_file(root_readme_path)
    text = replace_block(text, "DASHBOARD_WEEKS", "\n".join(["### 주차별 완료율 (%)", week_matrix_md()]))
    text = replace_block(text, "DASHBOARD_LEADERBOARD", leaderboard_md())
    text = replace_block(text, "DASHBOARD_TREND", trend_md())
    write_if_changed(root_readme_path, text)
    return True

# ---------- Submission week attribution ----------
def build_submission_attribution(weeks_cfg, participants) -> Dict[str, Dict[int, str]]:
    """
    반환: { seat(str) : { pid(int) : week_label("02","03",...) } }
    우선순위: squash merge 커밋 제목 → 브랜치명 → (없으면 배정 주차로 폴백)
    """
    problems_root = infer_problems_root(weeks_cfg)  # "problems"
    all_pids = set(pid for w in weeks_cfg for g in w["groups"] for pid in g["problems"])
    wk_label_by_pid = {}
    for w in weeks_cfg:
        lab = wk_label(w)
        for g in w["groups"]:
            for pid in g["problems"]:
                wk_label_by_pid[pid] = lab

    # seat 인덱스
    seat_by_branch_key = {}
    for m in participants:
        bk = _norm_token(m.get("branch_key") or m.get("name") or m.get("github"))
        seat_by_branch_key[bk] = str(m["seat"])

    # 1) 커밋 제목 기반 (main 히스토리)
    #    subject 예: "📄 submit: week03-keehoon (#25)"
    commit_attrib: Dict[str, Dict[int, str]] = {}
    try:
        log = _run("git log --grep='submit: week' --pretty=%H|%s --name-only --no-renames --first-parent origin/main || git log --grep='submit: week' --pretty=%H|%s --name-only --no-renames --first-parent main")
        chunks = re.split(r"\n(?=[0-9a-f]{7,40}\|)", log.strip(), flags=re.IGNORECASE)
        for ch in chunks:
            if "|" not in ch: continue
            head, *rest = ch.split("\n")
            _, subj = head.split("|", 1)
            m = re.search(r"submit:\s*week\s*(\d+)-([A-Za-z0-9_\-]+)", subj, flags=re.IGNORECASE)
            if not m: continue
            wk_lab = f"{int(m.group(1)):02d}"
            bkey = _norm_token(m.group(2))
            seat = seat_by_branch_key.get(bkey)
            if not seat: continue
            commit_attrib.setdefault(seat, {})
            for p in rest:
                p = p.strip()
                if not p or p.startswith((" ", "\t")):  # name-only block empty line skip
                    continue
                if problems_root + "/" not in p.replace("\\","/"):
                    continue
                m2 = re.search(r"boj_(\d+)", p)
                if not m2: continue
                pid = int(m2.group(1))
                if pid in all_pids:
                    commit_attrib[seat][pid] = wk_lab
    except Exception:
        if DEBUG: print("[debug] commit attribution skipped (git history not available)")

    # 2) 브랜치명 기반 (refs 전체)
    branch_attrib: Dict[str, Dict[int, str]] = {}
    refs = list_all_refs()
    week_branch_re = re.compile(r"week\s*(\d+)-([A-Za-z0-9_\-]+)", re.IGNORECASE)
    try:
        paths = paths_in_refs(refs, problems_root)
        for p in paths:
            m_pid = re.search(r"boj_(\d+)", p)
            if not m_pid: continue
            pid = int(m_pid.group(1))
            if pid not in all_pids: continue
            # 어떤 ref에서 온 파일인지 알 수 없으므로, ref별로 다시 조회(정확도↑)
            for r in refs:
                # 브랜치명이 weekXX-{name} 형태인지
                m_b = week_branch_re.search(r)
                if not m_b: continue
                wk_lab = f"{int(m_b.group(1)):02d}"
                bkey = _norm_token(m_b.group(2))
                seat = seat_by_branch_key.get(bkey)
                if not seat: continue
                # 해당 ref에서 이 파일이 존재?
                if p in list_paths_in_ref(r, problems_root):
                    # 소유자 확인까지 하고 매핑
                    # participants 중 seat의 멤버로 확인
                    member = next((mm for mm in participants if str(mm["seat"]) == seat), None)
                    if member and _member_owns_path(p, pid, member):
                        branch_attrib.setdefault(seat, {})
                        branch_attrib[seat].setdefault(pid, wk_lab)
    except Exception:
        if DEBUG: print("[debug] branch attribution skipped (git tree not available)")

    # 3) 병합 (commit > branch > assignment fallback)
    out: Dict[str, Dict[int, str]] = {}
    for m in participants:
        seat = str(m["seat"])
        out[seat] = {}
        # commit 우선
        for pid, wk_lab in commit_attrib.get(seat, {}).items():
            out[seat][pid] = wk_lab
        # branch 다음
        for pid, wk_lab in branch_attrib.get(seat, {}).items():
            out[seat].setdefault(pid, wk_lab)
        # fallback: 배정 주차(그래도 없을 때만)
        for pid in all_pids:
            out[seat].setdefault(pid, wk_label_by_pid.get(pid, ""))
    return out

# ---------- main ----------
def main():
    participants = load_yaml(PARTICIPANTS_YAML)["members"]
    weeks_cfg = load_yaml(WEEKS_YAML)["weeks"]
    participants = sorted(participants, key=lambda m: m["seat"])

    # Week READMEs
    states_bundle = {}  # week_id -> group_key -> {pid -> {seat -> 'PRE'|'DURING'|'NONE'}}
    for w in weeks_cfg:
        w_id = w["id"]
        states_bundle[w_id] = {}
        for g in w["groups"]:
            states = classify_states_repo(w, participants, g["problems"])
            states_bundle[w_id][g["key"]] = states
        # 멤버 열만 패치
        render_week_readme_members_only(w, participants, states_bundle[w_id])

    # Root README dashboards
    render_root_dashboards(ROOT_README, participants, weeks_cfg, states_bundle)

if __name__ == "__main__":
    main()
