#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ALSS Dashboard Builder (solved.ac + Git repo)
- Week README: ONLY update member columns (#1..#N)
  DURING: solved_by & repo(main or any branch) has member file
  PRE   : solved_by & no member file in repo
  NONE  : not solved_by
  * Old filename rule supported: week root: boj_{pid}_{member}.ext
  * Also supports {member}_{pid}(_N)?.ext and any path containing boj_{pid}
- Root README:
  1) 주차별 완료율(배정세트 기준, **DURING만 집계**)
  2) 전체 리더보드(동일, **DURING만 집계**)
  3) 멤버별 주차별 누적 추세(제출 주차 귀속 / **배정 누적 분모**, %)
     - 병합 PR: "submit: weekNN-<alias>" 커밋의 변경 파일
     - 미병합 브랜치: git diff main...<branch> 의 변경 파일
     - 폴백: ALSS_TREND_FALLBACK_DURING=1 이면 DURING을 배정 주차로 귀속
     - ✨ 누적 추세 분자/분모 일치: **분자도 배정 세트 내 PID만** 집계
NOTE: released_at 속성은 사용하지 않음.

Env:
  ALSS_OVERWRITE=1               # overwrite all member cells (default: 1; 0이면 빈칸만 채움)
  ALSS_CHECK_BRANCHES=1          # scan all refs/heads + refs/remotes (default: 1)
  ALSS_DEBUG=1                   # debug logs (default: 1)
  ALSS_TREND_FALLBACK_DURING=0   # trend 귀속 폴백(배정 주차로) 활성화 (default: 0)
  ALSS_LOG_LIMIT=0               # (선택) 커밋 스캔 상한(-n). 0 또는 미지정이면 무제한
"""

import os, re, time, math, subprocess, shlex, unicodedata
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
ALSS_TREND_FALLBACK_DURING = os.getenv("ALSS_TREND_FALLBACK_DURING", "0") == "1"

# ---------- solved.ac API ----------
SOLVED_BASE = "https://solved.ac/api/v3"
SESSION = requests.Session()
SESSION.headers.update({
    "User-Agent": "alss-dashboard/2.2 (+https://github.com/your/repo)",
})

def _get(url, params=None, max_retry=5):
    for _ in range(max_retry):
        r = SESSION.get(url, params=params, timeout=30)
        if r.status_code == 429:
            retry_after = int(r.headers.get("Retry-After", "3") or "3")
            time.sleep(max(3, retry_after))
            continue
        r.raise_for_status()
        time.sleep(0.25)  # gentle rate limit
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

def _find_col_idx(header_cells, exact, fuzzy):
    for key in exact:
        if key in header_cells:
            return header_cells.index(key)
    for i, c in enumerate(header_cells):
        cc = c.strip().lower()
        if any(fz in cc for fz in fuzzy):
            return i
    raise ValueError("column not found")

def patch_member_columns_in_block(block_md, pid_to_states, participants):
    lines = block_md.strip("\n").splitlines()
    if len(lines) < 2:
        return block_md

    # 표 헤더 찾기
    header_idx = None
    for i, ln in enumerate(lines):
        if ln.strip().startswith("|"):
            header_idx = i
            break
    if header_idx is None or header_idx + 1 >= len(lines):
        if DEBUG:
            print("[debug] header not found in block")
        return block_md

    header = _split_row(lines[header_idx])

    try:
        folder_col = _find_col_idx(header, exact=["폴더"], fuzzy=["폴더", "folder", "📁"])
        number_col = _find_col_idx(header, exact=["번호"], fuzzy=["번호", "no", "id"])
    except ValueError:
        if DEBUG:
            print(f"[debug] header parse failed: {header}")
        return block_md

    member_cols = list(range(folder_col + 1, len(header)))
    seats = [m["seat"] for m in participants]
    data_start = header_idx + 2  # header + separator

    for i in range(data_start, len(lines)):
        cells = _split_row(lines[i])
        if not cells or _is_separator_row(cells):
            continue

        # 문제 번호
        try:
            pid = int(re.sub(r"[^\d]", "", cells[number_col]))
        except ValueError:
            continue
        if pid not in pid_to_states:
            continue

        # 멤버 칸 덮어쓰기
        for idx, seat in enumerate(seats):
            col = member_cols[idx]
            state = pid_to_states[pid].get(str(seat), "NONE")
            sym = SYMBOL.get(state, SYMBOL["NONE"])
            if cells[col] != sym:
                if DEBUG:
                    print(f"[debug] patch: pid={pid} seat={seat} state={state} -> '{sym}' (was '{cells[col]}')")
                cells[col] = sym
            else:
                if DEBUG:
                    print(f"[debug] patch: pid={pid} seat={seat} state={state} (no change)")
        lines[i] = _join_row(cells)

    return "\n".join(lines)

def _replace_block_exact(text: str, marker: str, new_md_inside: str, s: int, e: int) -> str:
    return text[:s] + f"<!--START:{marker}-->\n\n{new_md_inside}\n\n<!--END:{marker}-->" + text[e:]

def render_week_readme_members_only(week_cfg, participants, states_by_group):
    path = os.path.join(ROOT_DIR, week_cfg["path"])
    text = read_file(path)
    changed = False

    for g in week_cfg["groups"]:
        marker = g.get("marker") or f"PROGRESS:{g['key']}"
        block, s, e = _get_block(text, marker)
        if s == -1:
            if DEBUG:
                print(f"[debug] no block found for marker='{marker}' in {path}")
            continue

        new_block = patch_member_columns_in_block(block.strip("\n"),
                                                  states_by_group[g["key"]],
                                                  participants)

        if new_block != block.strip("\n"):
            if DEBUG:
                print(f"[debug] block changed: {marker} in {path}")
            text = _replace_block_exact(text, marker, new_block, s, e)
            changed = True
        else:
            if DEBUG:
                print(f"[debug] block unchanged: {marker} in {path}")

    if changed:
        write_if_changed(path, text)
    return changed

# ---------- Member / Path matching ----------
ALLOWED_EXT = {".cpp",".cc",".cxx",".c",".py",".java",".kt",".js",".ts",
               ".rb",".go",".cs",".swift",".rs",".m",".mm"}

def _norm_token(s: str) -> str:
    # 한글/기호 경로의 정규화 문제를 없애기 위해 NFKC 적용
    s = unicodedata.normalize("NFKC", (s or ""))
    return re.sub(r"[\s_\-]+", "_", s.strip().lower())

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

def _path_tokens_without_ext(path: str) -> Set[str]:
    """경로의 모든 컴포넌트(확장자 제외)에서 토큰 추출."""
    parts = []
    for seg in path.replace("\\", "/").split("/"):
        if not seg:
            continue
        base, _ext = os.path.splitext(seg)
        if base:
            parts.append(base)
    toks = set()
    for p in parts:
        toks |= _split_tokens(p)
    return toks

def _member_owns_path(path: str, pid: int, member: dict) -> bool:
    """
    제출 파일 여부(견고 버전):
      - 경로(정규화) 안에 'boj_{pid}'가 있어야 함
      - 코드 파일 확장자여야 함
      - 파일명(확장자 제외)에 멤버 key( file_key / name / github 중 하나 )가 포함되면 DURING
      - 추가: 디렉터리 경로에도 멤버 key 토큰이 단독으로 등장하면 인정
    """
    p = path.replace("\\", "/")
    base = os.path.basename(p)
    base_noext, ext = os.path.splitext(base)
    if ext.lower() not in ALLOWED_EXT:
        return False

    pid_s = str(pid)
    klist = _member_keys_for_match(member)  # ['keehoon', 'noone_is_hier', ...]

    bn_norm = _norm_token(base_noext)  # 구분자 통일(대/소문자, -, _ 등)
    # 1) 파일명 패턴 확정 매치: <key>_(or -)<pid>(...)
    for k in klist:
        if re.match(rf"^{re.escape(k)}[_\-]{pid_s}(?:[_\-].*)?$", bn_norm):
            return True

    # 2) 디렉터리 구조 힌트: .../boj_<pid>.../ <basename startswith key>
    if re.search(rf"/boj_{pid_s}[^/]*/", p):
        for k in klist:
            if bn_norm.startswith(k + "_") or bn_norm.startswith(k + "-") or k in _split_tokens(base_noext):
                return True

    # 3) 보조 규칙(느슨): 경로 토큰 어딘가에 pid와 key가 공존
    all_toks = _path_tokens_without_ext(p)
    if (pid_s in all_toks) and any(k in all_toks for k in klist):
        return True

    return False

# ---------- Git helpers ----------
def _run(cmd: str, cwd: str = ROOT_DIR) -> str:
    return subprocess.check_output(cmd, shell=True, cwd=cwd, text=True, stderr=subprocess.DEVNULL)

def _clean_git_path(s: str) -> str:
    """git이 C-quoted로 내보낸 경로를 정리(양끝 따옴표 제거)"""
    if not s:
        return s
    s = s.strip()
    if len(s) >= 2 and s[0] == '"' and s[-1] == '"':
        s = s[1:-1]
    return s

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
    if DEBUG:
        print(f"[debug] refs detected: {len(order)} -> {', '.join(order[:12])}{' ...' if len(order)>12 else ''}")
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
        cmd = (
            f"git -c core.quotepath=off ls-tree -r --name-only "
            f"{shlex.quote(ref)} -- {shlex.quote(rel_path)}"
        )
        out = _run(cmd)
        return [_clean_git_path(ln.strip()) for ln in out.splitlines() if ln.strip()]
    except Exception:
        return []

def paths_in_refs(refs: List[str], rel_path: str) -> List[str]:
    seen, out = set(), []
    for r in refs:
        for p in list_paths_in_ref(r, rel_path):
            if p not in seen:
                seen.add(p); out.append(p)
    return out

def _resolve_main_ref() -> str:
    for ref in ["origin/main", "main", "HEAD"]:
        try:
            out = _run(f"git rev-parse --verify {shlex.quote(ref)}")
            if out.strip():
                return ref
        except Exception:
            continue
    return "HEAD"

def list_diff_paths_vs_main(ref_head: str, rel_path: str) -> List[str]:
    base = _resolve_main_ref()
    try:
        cmd = (
            f"git -c core.quotepath=off diff --name-only "
            f"{shlex.quote(base)}...{shlex.quote(ref_head)} -- {shlex.quote(rel_path)}"
        )
        out = _run(cmd)
        return [_clean_git_path(ln.strip()) for ln in out.splitlines() if ln.strip()]
    except Exception:
        return []

# ---------- Commit scan: full-history (no 1k cap) ----------
def _collect_submit_commits_unlimited(main_refs: List[str],
                                      limit_env_var: str = "ALSS_LOG_LIMIT"
                                     ) -> List[Tuple[str, str, List[str]]]:
    """
    main_refs 중 첫 번째로 유효한 ref에서 전체(or 제한) 히스토리를 읽어
    'submit: weekNN-<alias>' 커밋만 추출.
    반환: [(sha, subject, [paths...]), ...]
    - ALSS_LOG_LIMIT 환경변수로 선택적 상한(-n) 적용. 0/미지정이면 무제한.
    """
    out: List[Tuple[str, str, List[str]]] = []
    nopt = ""
    try:
        lim = int(os.getenv(limit_env_var, "").strip() or "0")
        if lim > 0:
            nopt = f"-n {lim}"
    except Exception:
        pass

    pat = re.compile(r"submit:\s*week\s*(\d+)-([A-Za-z0-9_\-]+)", re.IGNORECASE)

    for ref in main_refs:
        try:
            log = _run(f"git -c core.quotepath=off log {nopt} {shlex.quote(ref)} --pretty=%H|%s")
        except Exception:
            continue

        matched: List[Tuple[str, str]] = []
        for line in log.splitlines():
            if "|" not in line:
                continue
            sha, subj = line.split("|", 1)
            if pat.search(subj):
                matched.append((sha, subj))

        if not matched:
            continue

        for sha, subj in matched:
            try:
                files = _run(
                    f"git -c core.quotepath=off show {shlex.quote(sha)} "
                    f"--name-only --no-renames --pretty="
                )
                paths = [_clean_git_path(p.strip()) for p in files.splitlines() if p.strip()]
            except Exception:
                paths = []
            out.append((sha, subj, paths))

        if DEBUG:
            print(f"[debug] submit commits parsed on {ref}: {len(out)}")
        break

    return out

# ---------- Repo scanning: GLOBAL index (across all weeks/branches) ----------
def collect_repo_files_all(weeks_cfg, refs: List[str]) -> Dict[int, List[str]]:
    """
    모든 refs에서 problems/ 이하 파일을 모아 pid -> [paths...] 매핑
    """
    problems_root = infer_problems_root(weeks_cfg)
    paths = paths_in_refs(refs, problems_root)
    by_pid: Dict[int, List[str]] = {}
    for p in paths:
        m = re.search(r"boj_(\d+)", p)
        if not m:
            continue
        # ⬇⬇⬇ 추가: 소스 확장자만 수집
        ext = os.path.splitext(p)[1].lower()
        if ext not in ALLOWED_EXT:
            continue
        pid = int(m.group(1))
        by_pid.setdefault(pid, []).append(p)
    return by_pid

# ---------- DURING/PRE classification (repo-backed) ----------
def classify_states_repo(week_cfg, members, problems: List[int], repo_index_all: Dict[int, List[str]]) -> Dict[int, Dict[str, str]]:
    """
    DURING: solved_by AND (repo(any ref, any week dir) has member file)
    PRE   : solved_by AND (repo에 파일 없음)
    NONE  : solved_by 아님
    """
    pset = set(problems)
    results = {pid: {} for pid in problems}

    for m in members:
        seat = str(m["seat"])
        handle = m["solved_handle"]
        solved = solved_set(handle, restrict_ids=pset)
        if DEBUG:
            print(f"[debug] {handle} week={week_cfg['id']} solved={len(solved)} / assigned={len(pset)}")
        for pid in problems:
            if pid not in solved:
                results[pid][seat] = "NONE"; continue
            owned = any(_member_owns_path(path, pid, m) for path in repo_index_all.get(pid, []))
            if DEBUG and pid in solved:
                cand = repo_index_all.get(pid, [])
                print(f"[debug] DURING-check seat={seat} handle={handle} pid={pid} cand={len(cand)} -> {'DURING' if owned else 'PRE'}")
                # 후보는 있는데 매칭이 안 될 때 각 경로와 결과를 샘플로 보여줌
                if cand and not owned:
                    for p in cand[:6]:
                        ok = _member_owns_path(p, pid, m)
                        print(f"         try: member={m.get('file_key') or m.get('name') or m.get('github')} vs {p} => {ok}")
            results[pid][seat] = "DURING" if owned else "PRE"
    return results

# ---------- Submission week attribution ----------
def build_submission_attribution(weeks_cfg, participants, states_bundle=None) -> Dict[str, Dict[int, str]]:
    """
    반환: { seat(str) : { pid(int) : week_label("02","03",...) } }
    우선순위: squash 커밋 제목 → 브랜치명 → (옵션) DURING 폴백(배정 주차)
    """
    problems_root = infer_problems_root(weeks_cfg)
    all_pids = set(pid for w in weeks_cfg for g in w["groups"] for pid in g["problems"])
    wk_label_by_pid = {}
    for w in weeks_cfg:
        lab = f"{int(w['id']):02d}" if isinstance(w.get("id"), int) or str(w.get("id",""))
        else str(w.get("id",""))
        for g in w["groups"]:
            for pid in g["problems"]:
                wk_label_by_pid[pid] = lab

    # seat 인덱스
    seat_by_branch_key = { _norm_token(m.get("branch_key") or m.get("name") or m.get("github")) : str(m["seat"]) for m in participants }
    if DEBUG:
        print("[debug] seat_by_branch_key:", seat_by_branch_key)

    # 1) 커밋 제목 기반 (전체 히스토리 스캔)
    commit_attrib: Dict[str, Dict[int, str]] = {}
    main_refs = [_resolve_main_ref(), "HEAD", "origin/main", "main"]
    submit_commits = _collect_submit_commits_unlimited(main_refs)
    if DEBUG:
        print(f"[debug] main_refs tried: {main_refs}, submit_commits_found={len(submit_commits)>0}")

    pat_subj = re.compile(r"submit:\s*week\s*(\d+)-([A-Za-z0-9_\-]+)", re.IGNORECASE)
    for sha, subj, files in submit_commits:
        m = pat_subj.search(subj)
        if not m:
            continue
        wk_lab = f"{int(m.group(1)):02d}"
        bkey = _norm_token(m.group(2))
        seat = seat_by_branch_key.get(bkey)
        if not seat:
            continue
        member = next((mm for mm in participants if str(mm["seat"]) == seat), None)
        if not member:
            continue
        for p in files:
            if problems_root + "/" not in p.replace("\\","/"):
                continue
            m2 = re.search(r"boj_(\d+)", p)
            if not m2:
                continue
            pid = int(m2.group(1))
            if _member_owns_path(p, pid, member):
                # seat+pid dedup: dict key 덮어쓰기(같은 seat/pid 여러 파일은 1건)
                commit_attrib.setdefault(seat, {})[pid] = wk_lab

    # 2) 브랜치명 기반 (스냅샷 전체가 아니라, main...branch **diff**만 사용)
    branch_attrib: Dict[str, Dict[int, str]] = {}
    refs = list_all_refs()
    week_branch_re = re.compile(r"week\s*(\d+)-([A-Za-z0-9_\-]+)", re.IGNORECASE)
    for r in refs:
        mb = week_branch_re.search(r)
        if not mb: continue
        wk_lab = f"{int(mb.group(1)):02d}"
        bkey = _norm_token(mb.group(2))
        seat = seat_by_branch_key.get(bkey)
        if not seat: continue
        ps = list_diff_paths_vs_main(r, problems_root)
        if DEBUG:
            print(f"[debug] branch={r} week={wk_lab} diff_paths={len(ps)} (problems under)")
            for smp in ps[:6]:
                print("        -", smp)

        member = next((mm for mm in participants if str(mm["seat"]) == seat), None)
        for p in ps:
            m2 = re.search(r"boj_(\d+)", p)
            if not m2: continue
            pid = int(m2.group(1))
            if member and _member_owns_path(p, pid, member):
                branch_attrib.setdefault(seat, {})
                # seat+pid dedup: 최초 주차 유지, 이후 중복은 무시
                branch_attrib[seat].setdefault(pid, wk_lab)
            if DEBUG:
                print(f"[debug] branch-attr seat={seat} ref={r} week={wk_lab} pid={pid} path={p}")

    # 3) 병합 (commit > branch > (옵션) DURING 폴백)
    out: Dict[str, Dict[int, str]] = { str(m["seat"]): {} for m in participants }
    for seat, mp in commit_attrib.items():
        out[seat].update(mp)
    for seat, mp in branch_attrib.items():
        for pid, wk_lab in mp.items():
            out[seat].setdefault(pid, wk_lab)

    if ALSS_TREND_FALLBACK_DURING and states_bundle:
        for w in weeks_cfg:
            lab = f"{int(w['id']):02d}" if isinstance(w.get("id"), int) or str(w.get("id","")) else str(w.get("id",""))
            for g in w["groups"]:
                for pid, seat_states in states_bundle[w["id"]][g["key"]].items():
                    for m in participants:
                        seat = str(m["seat"])
                        # seat+pid dedup 유지: 기존 매핑 없고, DURING인 경우에만 채움
                        if pid not in out[seat] and seat_states.get(seat) == "DURING":
                            out[seat][pid] = lab

    if DEBUG:
        total_mapped = sum(len(v) for v in out.values())
        print(f"[debug] submission_attribution mapped pairs: {total_mapped}")
    return out

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
                    # DURING만 집계
                    if seat_states[seat] == "DURING":
                        solved.add(pid)
            solved_map[seat] = solved
        solved_by_member_per_week.append(solved_map)

    # 2) 제출 주차 귀속 맵
    submission_map = build_submission_attribution(
        weeks_cfg, participants,
        states_bundle if ALSS_TREND_FALLBACK_DURING else None
    )

    # 3-1) 주차별 완료율 (%): DURING만
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
        return "\n".join(lines)

    # 3-2) 전체 리더보드 (누적): DURING만 (유니크 PID 기준)
    def leaderboard_md():
        assigned_universe = set()
        for ws in week_sets:
            assigned_universe |= ws
        assigned_total = len(assigned_universe)

        scores = []
        for m in participants:
            seat = str(m["seat"])
            solved_union = set()
            for widx, ws in enumerate(week_sets):
                solved_union |= (solved_by_member_per_week[widx][seat] & ws)
            scores.append((m["name"], len(solved_union)))

        scores.sort(key=lambda x: x[1], reverse=True)
        lines = ["### 전체 리더보드 (누적)"]
        for i, (name, sc) in enumerate(scores, 1):
            rate = round(sc / assigned_total * 100) if assigned_total else 0
            lines.append(f"{i}) {name} — **{sc}/{assigned_total} ({rate}%)**")
        return "\n".join(lines)

    # 3-3) 멤버별 주차별 누적 추세 (제출 주차 귀속 / 배정 누적, %)
    def trend_md():
        # 분모: 1..k주차 배정 문제의 '합집합'(중복 제거)
        cumulative_assign_sets: List[Set[int]] = []
        acc = set()
        for ws in week_sets:
            acc |= ws
            cumulative_assign_sets.append(set(acc))

        if DEBUG:
            print("[trend] assigned_cum sizes:", [len(s) for s in cumulative_assign_sets])

        week_index = {lab: i for i, lab in enumerate(week_titles)}

        header = ["주차＼멤버"] + [m["name"] for m in participants]
        lines = ["| " + " | ".join(header) + " |",
                "|" + "---|" * (len(header)-1) + "---|"]

        for k, U in enumerate(cumulative_assign_sets):
            row = [week_titles[k]]
            denom = len(U)
            # 디버그 집계
            per_seat_dbg = {}
            for m in participants:
                seat = str(m["seat"])
                mp = submission_map.get(seat, {})  # { pid: "04", ... }
                # ✨ 분자: '해당 주차까지 제출' **AND** 배정 누적(U) 내에 포함된 고유 PID 수
                solved = sum(1 for _pid, wk_lab in mp.items()
                             if (_pid in U) and (wk_lab in week_index) and (week_index[wk_lab] <= k))
                rate = round(solved / denom * 100) if denom else 0
                row.append(f"{solved}/{denom} ({rate})")
                if DEBUG:
                    per_seat_dbg[seat] = solved
            if DEBUG:
                print(f"[trend] week={week_titles[k]} denom={denom} solved_by_seat={per_seat_dbg}")
            lines.append("| " + " | ".join(row) + " |")

        return "\n".join(
            ["### 멤버별 주차별 누적 추세 (제출 주차 귀속 / 배정 누적, %)"] + lines
        )

    text = read_file(root_readme_path)
    text = replace_block(text, "DASHBOARD_WEEKS", "\n".join(["### 주차별 완료율 (%)", week_matrix_md()]))
    text = replace_block(text, "DASHBOARD_LEADERBOARD", leaderboard_md())
    text = replace_block(text, "DASHBOARD_TREND", trend_md())
    write_if_changed(root_readme_path, text)
    return True

# ---------- main ----------
def main():
    participants = load_yaml(PARTICIPANTS_YAML)["members"]
    weeks_cfg = load_yaml(WEEKS_YAML)["weeks"]
    participants = sorted(participants, key=lambda m: m["seat"])

    # 전 브랜치/리모트 확보 전제: Actions에서 git fetch --all --prune --tags 수행 권장
    refs = list_all_refs()
    repo_index_all = collect_repo_files_all(weeks_cfg, refs)
    if DEBUG:
        target_pids_dbg = sorted({pid for w in weeks_cfg for g in w["groups"] for pid in g["problems"]})
        print(f"[debug] target_pids (weeks.yaml): {len(target_pids_dbg)}")
        # 각 PID에 대해 후보 경로가 몇 개 있는지(최대 8개만 샘플)
        for pid in target_pids_dbg[:30]:
            paths = repo_index_all.get(pid, [])
            print(f"[debug] pid={pid} candidates={len(paths)}")
            for p in paths[:8]:
                print("        -", p)

    # Week READMEs
    states_bundle = {}  # week_id -> group_key -> {pid -> {seat -> 'PRE'|'DURING'|'NONE'}}
    for w in weeks_cfg:
        w_id = w["id"]
        states_bundle[w_id] = {}
        for g in w["groups"]:
            states = classify_states_repo(w, participants, g["problems"], repo_index_all)
            states_bundle[w_id][g["key"]] = states
        # 멤버 열만 패치
        render_week_readme_members_only(w, participants, states_bundle[w_id])

    # Root README dashboards
    render_root_dashboards(ROOT_README, participants, weeks_cfg, states_bundle)

if __name__ == "__main__":
    main()
