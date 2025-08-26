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
     - 병합 PR: "submit: weekNN-<alias>" 커밋의 변경 파일(✅ git show --name-only)
     - 미병합 브랜치: (보조) git diff main...<branch> 의 변경 파일 (현재 주차만)
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
from typing import Dict, List, Set, Tuple, Optional
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

        # 멤버 칸 덮어쓰기 (옵션 존중)
        for idx, seat in enumerate(seats):
            col = member_cols[idx]
            state = pid_to_states[pid].get(str(seat), "NONE")
            sym = SYMBOL.get(state, SYMBOL["NONE"])
            if OVERWRITE_ALL_MEMBER_CELLS:
                do_write = (cells[col] != sym)
            else:
                do_write = is_blank_cell(cells[col]) and (cells[col] != sym)

            if do_write:
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
    # 1) 상대 경로 원본을 먼저 확인
    rel = (week_cfg.get("path") or "").strip()
    if not rel:
        if DEBUG:
            print(f"[debug] skip week README (empty path): id={week_cfg.get('id')}")
        return False

    # 2) 절대 경로 만들고 '파일'인지 확인
    path = os.path.join(ROOT_DIR, rel)
    if not os.path.isfile(path):  # 디렉터리/미존재 모두 스킵
        if DEBUG:
            print(f"[debug] skip week README (not a file): {path}")
        return False

    try:
        text = read_file(path)
    except Exception as e:
        if DEBUG:
            print(f"[debug] skip week README (read error): {path} ({e})")
        return False
    changed = False

    for g in week_cfg.get("groups", []):
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

def _list_changed_paths_for_commit(sha: str) -> List[str]:
    """
    merge 커밋 포함 변경 파일 안전 수집:
      1) git show -m --name-only --no-renames  (merge 분해)
      2) 폴백: git diff-tree -r -m --no-commit-id --name-only
    """
    # 1) show -m
    t1 = _decode_git(_run_bytes(
        f"git -c core.quotepath=off show -m --name-only --no-renames --pretty= {shlex.quote(sha)}"
    ))
    paths = [_clean_git_path(x.strip()) for x in t1.splitlines() if x.strip()]

    # 2) 폴백
    if not paths:
        t2 = _decode_git(_run_bytes(
            f"git -c core.quotepath=off diff-tree -r -m --no-commit-id --name-only {shlex.quote(sha)}"
        ))
        paths = [_clean_git_path(x.strip()) for x in t2.splitlines() if x.strip()]

    # 중복 제거(순서 유지)
    return list(dict.fromkeys(paths))

def _is_merge_commit(sha: str) -> bool:
    out = _decode_git(_run_bytes(f"git rev-list --parents -n 1 {shlex.quote(sha)}"))
    return len(out.strip().split()) >= 3  # parents가 2개 이상이면 merge

def _norm_token(s: str) -> str:
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
      - 코드 파일 확장자여야 함
      - 규칙 A: <name>_<pid>[_suffix]
      - 규칙 B: boj_<pid>_<name>
      - 규칙 C: 경로에 boj_<pid>가 있고 파일명에 멤버 key 힌트가 있으면 인정
      - 느슨: 경로 토큰에 pid와 멤버 key가 함께 존재하면 인정
    """
    p = path.replace("\\", "/")
    base = os.path.basename(p)
    base_noext, ext = os.path.splitext(base)
    if ext.lower() not in ALLOWED_EXT:
        return False

    pid_s = str(pid)
    klist = _member_keys_for_match(member)

    bn_norm = _norm_token(base_noext)
    # 규칙 A: <name>_<pid>[_suffix]
    for k in klist:
        if re.match(rf"^{re.escape(k)}_{pid_s}(?:_.+)?$", bn_norm):
            return True
    # 규칙 B: boj_<pid>_<name>
    for k in klist:
        if re.match(rf"^boj_{pid_s}_{re.escape(k)}(?:_.+)?$", bn_norm):
            return True
    # 디렉터리 힌트
    if re.search(rf"/boj_{pid_s}[^/]*/", p):
        for k in klist:
            if bn_norm.startswith(k + "_") or bn_norm.startswith(k + "-") or k in _split_tokens(base_noext):
                return True
    # 느슨: 토큰 공존
    all_toks = _path_tokens_without_ext(p)
    if (pid_s in all_toks) and any(k in all_toks for k in klist):
        return True
    return False

# ---------- Filename → (pid, seat) helper ----------
def _parse_pid_and_seat_from_basename(base_noext: str,
                                      participants,
                                      assigned_universe: Set[int]) -> Tuple[Optional[int], Optional[str]]:
    """
    파일명에서 PID와 seat 추정
      - 규칙 A: <name...>_<pid>(_<suffix>)?
      - 규칙 B: boj_<pid>_<name...>
    """
    bn = _norm_token(base_noext)

    # 규칙 B
    m = re.match(r"^boj_(\d{3,6})_(.+)$", bn)
    if m:
        try:
            pid = int(m.group(1))
        except Exception:
            pid = None
        name_part = m.group(2)
        name_tokens = set(name_part.split("_"))
        for mm in participants:
            seat = str(mm["seat"])
            for k in _member_keys_for_match(mm):
                if k in name_tokens:
                    return (pid if (pid in assigned_universe) else None, seat)
        return (pid if (pid in assigned_universe) else None, None)

    # 규칙 A
    m = re.match(r"^(.+?)_(\d{3,6})(?:_.+)?$", bn)
    if m:
        name_part = m.group(1)
        try:
            pid = int(m.group(2))
        except Exception:
            pid = None
        name_tokens = set(name_part.split("_"))
        for mm in participants:
            seat = str(mm["seat"])
            for k in _member_keys_for_match(mm):
                if k in name_tokens:
                    return (pid if (pid in assigned_universe) else None, seat)
        return (pid if (pid in assigned_universe) else None, None)

    return (None, None)

# ---------- Global PID extraction (A/B/C 모두 지원) ----------
PID_DIR_RE = re.compile(r"boj_(\d{3,6})")
PID_ANYNUM_RE = re.compile(r"(?<!\d)(\d{3,6})(?!\d)")

def _pid_from_path(path: str,
                   participants,
                   assigned_universe: Set[int]) -> Optional[int]:
    """
    경로에서 배정 PID 판별:
      1) 경로/디렉터리의 boj_#### 우선
      2) 파일명 규칙(_parse_pid_and_seat_from_basename 재사용)
      3) 마지막 폴백: 파일명 내 '단일' 숫자 토큰(3~6자리) 하나면 채택
    """
    p = path.replace("\\", "/")
    m = PID_DIR_RE.search(p)
    if m:
        pid = int(m.group(1))
        return pid if pid in assigned_universe else None

    base_noext = os.path.splitext(os.path.basename(p))[0]
    pid2, _seat_guess = _parse_pid_and_seat_from_basename(base_noext, participants, assigned_universe)
    if pid2:
        return pid2

    nums = [int(x) for x in PID_ANYNUM_RE.findall(base_noext)]
    nums = [n for n in nums if n in assigned_universe]
    return nums[0] if len(nums) == 1 else None

# ---------- Robust subprocess helpers (bytes + multi-decoding) ----------
def _run_bytes(cmd: str, cwd: str = ROOT_DIR) -> bytes:
    p = subprocess.Popen(cmd, shell=True, cwd=cwd,
                         stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    out, _ = p.communicate()
    return out or b""

def _decode_git(b: bytes) -> str:
    for enc in ("utf-8", "cp949", "euc-kr", "latin-1"):
        try:
            return b.decode(enc)
        except Exception:
            continue
    return b.decode("utf-8", errors="replace")

def _run(cmd: str, cwd: str = ROOT_DIR) -> str:
    return _decode_git(_run_bytes(cmd, cwd))

def _clean_git_path(s: str) -> str:
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
        p = (w.get("path") or "").strip()
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

# ---------- Submit commit scanning (MAIN ONLY, robust) ----------
SUBMIT_RE = re.compile(
    r"""submit\s*[:\]\uff1a]?\s*week\s*0*([0-9]{1,2})\s*[-–—_ ]\s*([A-Za-z0-9_\-]+)""",
    re.IGNORECASE | re.VERBOSE,
)

def collect_submit_commits_on_main(limit_env_var: str = "ALSS_LOG_LIMIT") -> List[Tuple[str, int, str, List[str]]]:
    """
    main 히스토리에서 'submit: week{번호}-{alias}' 커밋만 수집.
    반환: [(sha, ts, subject(NFKC), [changed_paths...])], 최신순

    변경 파일 목록 수집은 merge 커밋을 포함해 안전하게 동작하도록 다음 순서로 시도한다:
      1) git show -m --name-only --no-renames --pretty=
      2) (폴백) git diff-tree -r -m --no-commit-id --name-only

    환경변수:
      - {limit_env_var}: 최근 N개 커밋만 검사(0 또는 미설정이면 무제한)
    """
    ref = _resolve_main_ref()

    parts = [
        "git", "-c", "core.quotepath=off",
        "-c", "i18n.logOutputEncoding=UTF-8",
        "log", "--no-color",
    ]
    try:
        lim = int(os.getenv(limit_env_var, "").strip() or "0")
        if lim > 0:
            parts += ["-n", str(lim)]
    except Exception:
        pass

    parts += [f"--pretty=format:%H%x1f%ct%x1f%s%x1e", ref]
    cmd = " ".join(shlex.quote(x) for x in parts)

    raw_b = _run_bytes(cmd)
    raw = _decode_git(raw_b)
    recs = raw.split("\x1e")  # RS

    out: List[Tuple[str, int, str, List[str]]] = []

    def _safe_list_paths(sha: str) -> List[str]:
        try:
            return list(dict.fromkeys(_list_changed_paths_for_commit(sha)))
        except Exception:
            pass
        # 1) show -m
        t1 = _decode_git(_run_bytes(
            f"git -c core.quotepath=off show -m --name-only --no-renames --pretty= {shlex.quote(sha)}"
        ))
        paths = [_clean_git_path(x.strip()) for x in t1.splitlines() if x.strip()]
        # 2) 폴백: diff-tree -m
        if not paths:
            t2 = _decode_git(_run_bytes(
                f"git -c core.quotepath=off diff-tree -r -m --no-commit-id --name-only {shlex.quote(sha)}"
            ))
            paths = [_clean_git_path(x.strip()) for x in t2.splitlines() if x.strip()]
        return list(dict.fromkeys(paths))

    for rec in recs:
        if not rec.strip():
            continue
        cols = rec.split("\x1f")  # US
        if len(cols) < 3:
            continue

        sha, ts_s, subj = cols[0].strip(), cols[1].strip(), cols[2].strip()
        try:
            ts = int(ts_s)
        except Exception:
            ts = 0

        subj_norm = unicodedata.normalize("NFKC", subj)

        if not SUBMIT_RE.search(subj_norm):
            continue

        paths = _safe_list_paths(sha)

        if DEBUG:
            if not paths:
                try:
                    mflag = _is_merge_commit(sha)
                except Exception:
                    mflag = False
                print(f"[debug] submit-commit has NO files (merge={mflag}) sha={sha} subj={subj_norm}")
            else:
                print(f"[debug] submit-commit files: {len(paths)} sha={sha}")

        out.append((sha, ts, subj_norm, paths))

    if DEBUG:
        print(f"[debug] submit commits parsed on {ref}: {len(out)}")
    return out

# ---------- Repo scanning: GLOBAL index (across all weeks/branches) ----------
def collect_repo_files_all(weeks_cfg, refs: List[str], participants) -> Dict[int, List[str]]:
    """
    모든 refs에서 problems/ 이하 파일을 모아 pid -> [paths...] 매핑
    (파일명만으로 PID가 있는 경우도 포함: 케이스 B 대응)
    """
    problems_root = infer_problems_root(weeks_cfg)
    # 배정 PID 유니버스
    assigned_universe: Set[int] = set(
        pid
        for w in weeks_cfg
        for g in (w.get("groups") or [])
        for pid in g.get("problems", [])
    )
    all_paths = paths_in_refs(refs, problems_root)
    by_pid: Dict[int, List[str]] = {}
    for p in all_paths:
        ext = os.path.splitext(p)[1].lower()
        if ext not in ALLOWED_EXT:
            continue
        pid = _pid_from_path(p, participants, assigned_universe)
        if pid is None:
            continue
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
                if cand and not owned:
                    for p in cand[:6]:
                        ok = _member_owns_path(p, pid, m)
                        print(f"         try: member={m.get('file_key') or m.get('name') or m.get('github')} vs {p} => {ok}")
            results[pid][seat] = "DURING" if owned else "PRE"
    return results

# ---------- Submission week attribution (commit first, current-branch as backup) ----------
def build_submission_attribution(weeks_cfg, participants, states_bundle) -> Dict[str, Dict[int, str]]:
    """
    반환: { seat(str) : { pid(int) : week_label("01","02",...) } }

    ★ 핵심 규칙(요청사항 반영):
      1) DURING PID 집합을 좌석별로 먼저 만든다(표1 계산 때 만든 것과 동일, '진실').
      2) submit PR 커밋을 '주차 오름차순'으로 순회하면서,
         - 각 커밋이 바꾼 파일에서 PID를 뽑고
         - 그 PID가 해당 좌석의 DURING에 있고
         - 아직 어떤 주차에도 '귀속되지 않았다'면
           → 해당 주차(wk)에 '최초 등장'으로 귀속한다.
      3) (보조) 현재 주차 브랜치 diff에서도 동일 규칙으로 보정(아직 귀속 안 된 DURING만).
      4) (옵션) ALSS_TREND_FALLBACK_DURING=1 이면, 끝까지 귀속 안 된 DURING을 배정 주차로 폴백.
    """
    problems_root = infer_problems_root(weeks_cfg)

    # 배정 PID 유니버스 (모든 주차의 problems 합집합)
    assigned_universe: Set[int] = {
        pid
        for w in weeks_cfg
        for g in (w.get("groups") or [])
        for pid in g.get("problems", [])
    }

    # 좌석 alias 매핑 (submit: weekNN-<alias> -> seat)
    seat_by_branch_key: Dict[str, str] = {}
    seats_order = []
    for m in sorted(participants, key=lambda x: int(x["seat"])):
        seat = str(m["seat"])
        seats_order.append(seat)
        for key in [m.get("branch_key"), m.get("file_key"), m.get("name"), m.get("github")]:
            if key:
                seat_by_branch_key[_norm_token(key)] = seat
    if DEBUG:
        print("[debug] seat_by_branch_key:", seat_by_branch_key)

    # ★ DURING PID 집합(좌석별 ground truth)
    during_by_seat: Dict[str, Set[int]] = {str(m["seat"]): set() for m in participants}
    for w in weeks_cfg:
        for g in (w.get("groups") or []):
            group_states = states_bundle[w["id"]][g["key"]]
            for pid, seat_states in group_states.items():
                for m in participants:
                    seat = str(m["seat"])
                    if seat_states.get(seat) == "DURING":
                        during_by_seat[seat].add(pid)
    if DEBUG:
        print("[debug][trend] DURING_by_seat_sizes:", {s: len(v) for s, v in during_by_seat.items()})

    # ★ 주차 라벨(숫자만) 오름차순
    week_labels_sorted: List[str] = sorted(
        [f"{int(w.get('id')):02d}" for w in weeks_cfg if str(w.get("id", "")).isdigit()],
        key=lambda s: int(s)
    )

    # ★ 커밋 → (seat, week)별 PID 후보 사전: seats × weeks
    commits = collect_submit_commits_on_main()
    cand_by_seat_week: Dict[str, Dict[str, Set[int]]] = {s: {} for s in seats_order}

    for _sha, _ts, subj, files in commits:
        m = SUBMIT_RE.search(subj)
        if not m:
            continue
        wk_lab = f"{int(m.group(1)):02d}"
        alias_key = _norm_token(m.group(2))
        seat = seat_by_branch_key.get(alias_key)
        if not seat:
            continue

        for p in files:
            ext = os.path.splitext(p)[1].lower()
            if ext not in ALLOWED_EXT:
                continue
            # problems/ 이하만 강제하지 말고, PID만 제대로 뽑히면 인정
            pid = _pid_from_path(p, participants, assigned_universe)
            if pid is None:
                continue
            # ★ 해당 좌석이 DURING이 아닌 PID는 애초에 분자 후보로 보지 않음
            if pid not in during_by_seat[seat]:
                continue
            cand_by_seat_week.setdefault(seat, {}).setdefault(wk_lab, set()).add(pid)

    if DEBUG:
        dbg = {s: {wk: len(ps) for wk, ps in sorted(wmap.items())} for s, wmap in cand_by_seat_week.items()}
        print("[debug][trend] commit_candidates_by_seat_week:", dbg)

    # ★ 최초-등장 귀속: 주차 오름차순으로 '처음 본 DURING PID'만 매핑
    submission_map: Dict[str, Dict[int, str]] = {s: {} for s in seats_order}
    seen_by_seat: Dict[str, Set[int]] = {s: set() for s in seats_order}

    for wk in week_labels_sorted:               # 01 → 02 → 03 → ...
        for seat in seats_order:                # 좌석 순회
            for pid in sorted(cand_by_seat_week.get(seat, {}).get(wk, set())):
                if pid in seen_by_seat[seat]:   # 이미 이전 주차에 귀속됨
                    continue
                # DURING 보증은 위 cand 구성 단계에서 이미 통과
                submission_map[seat][pid] = wk
                seen_by_seat[seat].add(pid)

    # ★ (보조) 브랜치 diff 보정: 모든 weekNN-<alias> 브랜치를 스캔하여 해당 주차로 귀속
    if CHECK_BRANCHES and week_labels_sorted:
        refs = list_all_refs()
        problems_root = infer_problems_root(weeks_cfg)

        for wk in week_labels_sorted:  # '01','02','03','04'... 오름차순
            wk_int = int(wk)

            for r in refs:
                # ref 예시: 'week04-keehoon', 'origin/week04-keehoon', 'remotes/origin/week04-keehoon'
                base = r.split("/")[-1]  # 마지막 세그먼트만 추출하여 앵커 매칭
                m = re.match(rf"^week\s*0*{wk_int}-([A-Za-z0-9_\-]+)$", base, re.IGNORECASE)
                if not m:
                    continue

                alias_key = _norm_token(m.group(1))
                seat = seat_by_branch_key.get(alias_key)
                if not seat:
                    continue

                diff_paths = list_diff_paths_vs_main(r, problems_root)
                if DEBUG:
                    print(f"[debug] branch-match: ref={r} wk={wk} alias={alias_key} diff_paths={len(diff_paths)}")

                for p in diff_paths:
                    if problems_root + "/" not in p:
                        continue
                    ext = os.path.splitext(p)[1].lower()
                    if ext not in ALLOWED_EXT:
                        continue

                    pid = _pid_from_path(p, participants, assigned_universe)
                    if pid is None:
                        continue
                    # DURING이 아닌 PID는 분자 후보에서 제외
                    if pid not in during_by_seat[seat]:
                        continue
                    # 이미 더 이른 주차에 귀속된 PID는 건너뜀(earliest wins)
                    if pid in seen_by_seat[seat]:
                        continue

                    submission_map[seat][pid] = wk
                    seen_by_seat[seat].add(pid)

    # ★ (옵션) DURING 폴백: 끝까지 귀속 안 된 DURING → 배정 주차로
    if ALSS_TREND_FALLBACK_DURING:
        assign_by_lab: Dict[str, Set[int]] = {}
        for w in weeks_cfg:
            lab = f"{int(w['id']):02d}" if str(w.get("id", "")).isdigit() else str(w.get("id", ""))
            ws = set(pid for g in (w.get("groups") or []) for pid in g.get("problems", []))
            assign_by_lab[lab] = ws
        for seat, during_set in during_by_seat.items():
            for pid in during_set:
                if pid in submission_map[seat]:
                    continue
                for wk in week_labels_sorted:
                    if pid in assign_by_lab.get(wk, set()):
                        submission_map[seat][pid] = wk
                        break

    # 디버그: 주차·좌석별 분자 분포 및 합계
    if DEBUG:
        by_seat_week = {}
        for seat, mp in submission_map.items():
            agg = {}
            for pid, wk in mp.items():
                agg[wk] = agg.get(wk, 0) + 1
            by_seat_week[seat] = dict(sorted(agg.items()))
        print("[debug][trend] submission_by_seat_week:", by_seat_week)
        totals = {s: sum(d.values()) for s, d in by_seat_week.items()}
        total_mapped = sum(totals.values())
        print("[debug] submission_attribution mapped pairs:", total_mapped)
        print("[debug] per-seat counts:", totals)

    return submission_map

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
        pids = set(pid for g in w.get("groups", []) for pid in g.get("problems", []))
        week_sets.append(pids)
        week_titles.append(wk_label(w))

        solved_map: Dict[str, Set[int]] = {}
        for m in participants:
            seat = str(m["seat"])
            solved = set()
            for g in w.get("groups", []):
                for pid, seat_states in states_bundle[w["id"]][g["key"]].items():
                    # DURING만 집계
                    if seat_states[seat] == "DURING":
                        solved.add(pid)
            solved_map[seat] = solved
        solved_by_member_per_week.append(solved_map)

    # 2) 제출 주차 귀속 맵
    submission_map = build_submission_attribution(weeks_cfg, participants, states_bundle)

    # 3-1) 주차별 완료율 (%): DURING만
    def week_matrix_md():
        header = ["주차＼멤버"] + [m["name"] for m in participants] + ["합계(%)"]
        lines = ["| " + " | ".join(header) + " |",
                 "|" + "---|" * (len(header)-1) + "---|"]
        col_tot_solved = [0]*len(participants)
        col_tot_assign = [0]*len(participants)

        for widx, ws in enumerate(week_sets):
            assign = len(ws)
            w_cfg = weeks_cfg[widx] if widx < len(weeks_cfg) else {}
            if assign == 0:
                if DEBUG and not (w_cfg.get("groups") or []):
                    print(f"[debug] week {w_cfg.get('id')} has no groups (dummy week)")
                continue  # 더미(배정 0) 주차는 완료율 표에서 숨김

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
            row.append(str(round(row_sum / (assign*len(participants)) * 100)))
            lines.append("| " + " | ".join(row) + " |")

        tot = ["합계(%)"]
        for mi in range(len(participants)):
            rate = round(col_tot_solved[mi] / col_tot_assign[mi] * 100) if col_tot_assign[mi] else 0
            tot.append(str(rate))
        overall = round(sum(col_tot_solved) / sum(col_tot_assign) * 100) if sum(col_tot_assign) else 0
        tot.append(str(overall))
        lines.append("| " + " | ".join(tot) + " |")
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

        if DEBUG:
            # 좌석별 DURING 누적(ground truth)
            labs = [wk_label(w) for w in weeks_cfg]
            week_sets_local = [set(pid for g in w.get("groups", []) for pid in g.get("problems", [])) for w in weeks_cfg]
            during_cumu = {}
            seen_by_seat = {str(m["seat"]): set() for m in participants}
            for i, lab in enumerate(labs):
                U = set().union(*week_sets_local[:i+1])
                row = {}
                for m in participants:
                    seat = str(m["seat"])
                    # 이번 라벨까지 DURING PID 누적
                    for w in weeks_cfg[:i+1]:
                        for g in w.get("groups", []):
                            for pid, st in states_bundle[w["id"]][g["key"]].items():
                                if st[seat] == "DURING":
                                    seen_by_seat[seat].add(pid)
                    row[seat] = len([p for p in seen_by_seat[seat] if p in U])
                during_cumu[lab] = row
            print("[debug] DURING cumu (per seat):", during_cumu)

        # 1) 제출 귀속에서 나온 주차 라벨 수집
        labels_from_submission = {wk for seat_map in submission_map.values() for wk in seat_map.values()}

        # 2) 라벨 정렬 키
        def _wk_key(s):
            s = str(s)
            return (0, int(s)) if re.fullmatch(r"\d+", s) else (1, s)

        # 3) 표 행 라벨 = 배정 주차 ∪ 귀속 주차
        all_labels = sorted(set(week_titles) | labels_from_submission, key=_wk_key)
        label_pos = {lab: i for i, lab in enumerate(all_labels)}

        # 4) 분모(배정 누적 집합)
        cumulative_assign_sets_all = []
        for i, lab in enumerate(all_labels):
            U = set()
            for wl, ws in zip(week_titles, week_sets):
                if label_pos[wl] <= i:
                    U |= ws
            cumulative_assign_sets_all.append(U)

        # 5) 표 렌더링
        header = ["주차＼멤버"] + [m["name"] for m in participants]
        lines = ["| " + " | ".join(header) + " |",
                 "|" + "---|" * (len(header)-1) + "---|"]

        for i, (lab, U) in enumerate(zip(all_labels, cumulative_assign_sets_all)):
            denom = len(U)
            row = [lab]
            for m in participants:
                seat = str(m["seat"])
                mp = submission_map.get(seat, {})
                solved = sum(
                    1
                    for pid, wk_lab in mp.items()
                    if (pid in U) and (wk_lab in label_pos) and (label_pos[wk_lab] <= i)
                )
                rate = round(solved / denom * 100) if denom else 0
                row.append(f"{solved}/{denom} ({rate})")
            lines.append("| " + " | ".join(row) + " |")

        out_md = "\n".join(
            ["### 멤버별 주차별 누적 추세 (제출 주차 귀속 / 배정 누적, %)"] + lines
        )

        if DEBUG and all_labels:
            # 최종 행 검증(좌석별 누적 분자 합)
            last_label = all_labels[-1]
            final_totals = {str(m["seat"]): 0 for m in participants}
            for m in participants:
                seat = str(m["seat"])
                mp = submission_map.get(seat, {})
                final_totals[seat] = sum(
                    1 for _, wk in mp.items()
                    if wk in label_pos and label_pos[wk] <= label_pos[last_label]
                )
            print("[debug][trend] final_row_totals_from_submission:", final_totals)

        return out_md

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
    repo_index_all = collect_repo_files_all(weeks_cfg, refs, participants)
    if DEBUG:
        target_pids_dbg = sorted({pid for w in weeks_cfg for g in w.get("groups", []) for pid in g.get("problems", [])})
        print(f"[debug] target_pids (weeks.yaml): {len(target_pids_dbg)}")
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
        for g in w.get("groups", []):
            states = classify_states_repo(w, participants, g["problems"], repo_index_all)
            states_bundle[w_id][g["key"]] = states
        # 멤버 열만 패치
        render_week_readme_members_only(w, participants, states_bundle[w_id])

    # Root README dashboards
    render_root_dashboards(ROOT_README, participants, weeks_cfg, states_bundle)

if __name__ == "__main__":
    main()
