#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
BOJ 문제 폴더 자동 세팅 봇 (requests + BeautifulSoup + solved.ac)
- 폴더명 'boj_<id>_...' 또는 --id <id>
- BOJ: 제목/시간/메모리/샘플(입·출력) 파싱 (개행/CR 정규화)
- solved.ac: 티어/태그/푼 사람 수/평균 시도 → 소스 상단 주석으로 주입
- tests/sample*.in|.out 생성, input.txt 편의 복사
- run.sh 생성(언어 공통): 소스 1개 선택 → tests의 모든 .in 실행 & .out 검증
- 파일/폴더 규칙
  * 일반: 파일명 = username_pid.(cpp|py|java)
  * 지정경로 모드(--dest / --dest-base / BOJ_DEST_BASE):
      - 폴더명 = <id>.<제목_정제>
      - 파일명 = <id>.<제목_정제>.(cpp|py|java)

의존: requests, bs4, lxml
"""

import argparse
import os
import re
import sys
import textwrap
import time, shutil, subprocess
import html as ihtml
from pathlib import Path
from typing import List, Tuple, Optional, Dict, Any

import requests
from bs4 import BeautifulSoup

BOJ_BASE = "https://www.acmicpc.net/problem/"
SOLVED_SHOW = "https://solved.ac/api/v3/problem/show?problemId={pid}"

HEADERS = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)",
    "Accept": "text/html,application/xhtml+xml,application/json",
    "Accept-Language": "ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7",
    "Referer": "https://www.acmicpc.net/",
    "Connection": "close",
}

# ─────────────────────────────────────────────────────────────────────────────
# Console Encoding Setup (Force UTF-8 Output)
#   - Git Bash, Windows Console 등 환경별 인코딩 차이로 인한 모지바케 방지
#   - stdout/stderr를 UTF-8로 재설정 (Python 3.7+)
# ─────────────────────────────────────────────────────────────────────────────

def _supports_utf8() -> bool:
    enc = (sys.stdout.encoding or '') + (sys.stderr.encoding or '')
    return 'UTF' in enc.upper()

try:
    # Python 3.7+ : 표준 출력 인코딩을 강제로 UTF-8로
    sys.stdout.reconfigure(encoding='utf-8', errors='replace')
    sys.stderr.reconfigure(encoding='utf-8', errors='replace')
except Exception:
    # 못 바꾸는 환경 대비
    os.environ.setdefault('PYTHONIOENCODING', 'utf-8')

OK = "✅" if _supports_utf8() else "[OK]"
WARN = "⚠️" if _supports_utf8() else "[WARN]"
SKIP = "⏭" if _supports_utf8() else "[SKIP]"

# ─────────────────────────────────────────────────────────────────────────────
# Args & Lang normalize
# ─────────────────────────────────────────────────────────────────────────────
def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(
        description="BOJ 문제 폴더 자동 세팅 봇",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=textwrap.dedent("""
        예)
          python boj_init.py cpp --id 17608
          # 기본 경로 환경변수 사용(BOJ_DEST_BASE) + 폴더 생성/진행
          python boj_init.py cpp --id 17608 --dest
          # 기본 경로 뒤에 suffix를 붙임
          python boj_init.py cpp --id 17608 --dest +week02/스택
          # 기본 경로를 옵션으로 직접 지정
          python boj_init.py cpp --id 17608 --dest-base "C:/TIS/Baekjoon" --dest +week02/스택
          # 생성 후 즉시 채점(해당 소스만 지정해 자동 실행)
          python boj_init.py java --id 1006 --dest +week02 && ./run.sh "1006.문제제목.java"
        """),
    )
    p.add_argument("lang", choices=["cpp","py","java","c++","cpp14","python"], help="언어")
    p.add_argument("--id", type=int, help="문제 번호(미지정시 폴더명에서 추출)")
    p.add_argument("--username", default="keehoon", help="일반 모드 파일명(username_pid)의 username 부분")
    p.add_argument("--run", action="store_true", help="생성 후 즉시 run.sh로 채점 실행(해당 소스 자동 선택)")
    p.add_argument("--no-solvedac", action="store_true", help="solved.ac 조회 비활성화")
    p.add_argument("--max-tags", type=int, default=8, help="주석에 표시할 최대 태그 수 (기본 8)")
    p.add_argument("--debug", action="store_true", help="요청/리트라이 상세 로그 출력")
    p.add_argument("--insecure", action="store_true", help="인증서 검증 비활성화(임시용)")
    p.add_argument("--force", "-f", action="store_true", help="기존 파일이 있어도 덮어쓰기(기본: 건너뜀)")

    # 지정경로: --dest은 값이 없어도 허용(기본경로만 사용), '+suffix' 또는 경로 문자열도 허용
    p.add_argument("--dest", nargs="?", const="", type=str,
                   help="문제 폴더를 지정 경로에 생성해 그 폴더에서 작업. "
                        "값이 없으면 --dest-base/BOJ_DEST_BASE만 사용, "
                        "'+suffix'면 기본경로 뒤에 덧붙임, 경로 문자열이면 그 경로 사용.")
    p.add_argument("--dest-base", type=str,
                   help="지정경로 기본값. 미지정 시 환경변수 BOJ_DEST_BASE 사용")

    em = p.add_mutually_exclusive_group()
    em.add_argument("--tier-emoji", dest="tier_emoji", action="store_true", help="티어 이모지 사용")
    em.add_argument("--no-tier-emoji", dest="tier_emoji", action="store_false", help="티어 이모지 비활성화")
    p.set_defaults(tier_emoji=True)
    return p.parse_args()

def normalize_lang(lang: str) -> str:
    if lang in ["cpp","c++","cpp14"]: return "cpp"
    if lang in ["py","python"]: return "py"
    return "java"

def infer_id_from_dir() -> Optional[int]:
    name = Path.cwd().name
    m = re.match(r"^[Bb][Oo][Jj]_([0-9]+)_.*$", name)
    if m: return int(m.group(1))
    m = re.match(r"^([0-9]+)[._-].*$", name)  # 17608.제목 / 17608_제목 / 17608-제목
    if m: return int(m.group(1))
    return None

# ─────────────────────────────────────────────────────────────────────────────
# Sample text clean
# ─────────────────────────────────────────────────────────────────────────────
def clean_sample_text(s: str) -> str:
    if s is None:
        return ""
    s = ihtml.unescape(s)
    s = s.replace("\r\n", "\n").replace("\r", "\n")
    s = re.sub(r"\n{3,}", "\n\n", s)
    s = re.sub(r"\n+\n", "\n\n", s)  # 과도한 빈줄 압축
    s = re.sub(r"[ \t]+$", "", s, flags=re.M).strip("\n") + "\n"
    return s

# ─────────────────────────────────────────────────────────────────────────────
# Naming helpers
# ─────────────────────────────────────────────────────────────────────────────
def sanitize_java_identifier(name: str) -> str:
    s = re.sub(r"[^A-Za-z0-9_]", "_", name)
    if not s: s = "_"
    if s[0].isdigit(): s = "_" + s
    return s

def unified_basename(username: str, pid: int) -> str:
    return sanitize_java_identifier(f"{username}_{pid}")

# ─────────────────────────────────────────────────────────────────────────────
# Dest path helpers
# ─────────────────────────────────────────────────────────────────────────────
_FORBID_MAP = {"/":"／","\\":"＼","?":"？",":":"：","*":"＊","\"":"＂","<":"＜",">":"＞","|":"｜"}
_RESERVED_WIN = re.compile(r"^(CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])$", re.IGNORECASE)

def sanitize_title_for_dir(title: str) -> str:
    s = "".join(ch for ch in title if ord(ch) >= 32)
    for k,v in _FORBID_MAP.items(): s = s.replace(k, v)
    s = re.sub(r"\s+", "_", s.strip())
    s = re.sub(r"_+", "_", s)
    s = re.sub(r"[ .]+$", "", s)
    s = re.sub(r"^\.+", "", s)
    if not s: s = "_"
    if _RESERVED_WIN.match(s): s = "_" + s
    return s

def resolve_dest_path(args) -> Optional[Path]:
    base = args.dest_base or os.environ.get("BOJ_DEST_BASE")
    if args.dest is None:
        return None
    if args.dest == "":
        if not base:
            raise ValueError("--dest 사용 시 --dest-base 또는 BOJ_DEST_BASE가 필요합니다.")
        return Path(base).expanduser()
    if args.dest.startswith("+"):
        if not base:
            raise ValueError("--dest +suffix 사용 시 --dest-base 또는 BOJ_DEST_BASE가 필요합니다.")
        return (Path(base).expanduser() / args.dest[1:]).resolve()
    return Path(args.dest).expanduser().resolve()

def make_problem_folder(parent: Path, name: str) -> Path:
    target = parent / name
    target.mkdir(parents=True, exist_ok=True)
    return target

# ─────────────────────────────────────────────────────────────────────────────
# HTTP helpers
# ─────────────────────────────────────────────────────────────────────────────
def http_get_text(url: str, *, verify: bool=True, debug: bool=False) -> str:
    sess = requests.Session()
    sess.headers.update(HEADERS)
    for i in range(3):
        try:
            r = sess.get(url, timeout=10, verify=verify, allow_redirects=True)
            if debug: print(f"[GET {i+1}/3] {r.status_code} {r.reason}", file=sys.stderr)
            if r.status_code == 200: return r.text
            time.sleep(1 + i)
        except requests.RequestException as e:
            if debug: print(f"[GET {i+1}/3] EXC: {e}", file=sys.stderr)
            time.sleep(1 + i)
    if shutil.which("curl"):
        try:
            if debug: print("[curl fallback] running curl -fsSL ...", file=sys.stderr)
            out = subprocess.check_output(["curl","-fsSL","-A",HEADERS["User-Agent"], url], text=True)
            return out
        except Exception as e:
            if debug: print(f"[curl fallback] EXC: {e}", file=sys.stderr)
    raise RuntimeError(f"페이지 요청 실패: {url}")

def http_get_json(url: str) -> Optional[Dict[str, Any]]:
    for _ in range(3):
        try:
            r = requests.get(url, headers=HEADERS, timeout=10)
            if r.status_code == 200: return r.json()
        except requests.RequestException:
            pass
    return None

# ─────────────────────────────────────────────────────────────────────────────
# BOJ parsing
# ─────────────────────────────────────────────────────────────────────────────
def extract_text(el) -> str:
    return el.get_text("\n").strip()

def parse_problem(html: str) -> dict:
    soup = BeautifulSoup(html, "lxml")

    title = ""
    title_span = soup.select_one("#problem_title")
    if title_span: title = extract_text(title_span)
    if not title:
        t = soup.select_one("head > title")
        if t:
            raw = extract_text(t)
            title = re.sub(r"^\s*\d+\s*[:\-]\s*", "", raw)
            title = re.sub(r"\s*-\s*.*$", "", title).strip()

    time_limit = None
    memory_limit = None
    info_table = soup.select_one(".problem-info, .table-responsive table")
    if info_table:
        text_blob = extract_text(info_table)
        m = re.search(r"시간\s*제한\s*([^\n]+)", text_blob) or re.search(r"Time\s*Limit\s*:?[\s]*([^\n]+)", text_blob, re.I)
        if m: time_limit = m.group(1).strip()
        m = re.search(r"메모리\s*제한\s*([^\n]+)", text_blob) or re.search(r"Memory\s*Limit\s*:?[\s]*([^\n]+)", text_blob, re.I)
        if m: memory_limit = m.group(1).strip()

    samples: List[Tuple[str, str]] = []
    input_pres = soup.select('pre[id^="sample-input"]')
    output_pres = soup.select('pre[id^="sample-output"]')

    def sort_key(pre):
        m = re.search(r"(\d+)$", pre.get("id",""))
        return int(m.group(1)) if m else 0

    input_pres.sort(key=sort_key); output_pres.sort(key=sort_key)

    if input_pres and output_pres and len(input_pres) == len(output_pres):
        for ip, op in zip(input_pres, output_pres):
            iin  = clean_sample_text(extract_text(ip))
            oout = clean_sample_text(extract_text(op))
            samples.append((iin, oout))
    else:
        def collect_by_heading(patterns: List[str]) -> List[str]:
            texts = []
            for h in soup.select("h3, h4, h5"):
                label = extract_text(h)
                if any(pat.lower() in label.lower() for pat in patterns):
                    nxt_pre = h.find_next("pre")
                    if nxt_pre: texts.append(extract_text(nxt_pre))
            return texts
        ins = collect_by_heading(["예제 입력", "Sample Input"])
        outs = collect_by_heading(["예제 출력", "Sample Output"])
        for i in range(max(len(ins), len(outs))):
            samples.append((clean_sample_text(ins[i] if i < len(ins) else ""),
                            clean_sample_text(outs[i] if i < len(outs) else "")))

    return {"title": title, "time_limit": time_limit, "memory_limit": memory_limit, "samples": samples}

# ─────────────────────────────────────────────────────────────────────────────
# solved.ac helpers
# ─────────────────────────────────────────────────────────────────────────────
TIER_NAMES = [None,
    "Bronze V","Bronze IV","Bronze III","Bronze II","Bronze I",
    "Silver V","Silver IV","Silver III","Silver II","Silver I",
    "Gold V","Gold IV","Gold III","Gold II","Gold I",
    "Platinum V","Platinum IV","Platinum III","Platinum II","Platinum I",
    "Diamond V","Diamond IV","Diamond III","Diamond II","Diamond I",
    "Ruby V","Ruby IV","Ruby III","Ruby II","Ruby I"
]

def level_to_name(level: Optional[int]) -> Optional[str]:
    if isinstance(level, int) and 1 <= level < len(TIER_NAMES): return TIER_NAMES[level]
    return None

def tier_icon(tier_name: Optional[str]) -> str:
    if not tier_name: return ""
    return {"Bronze":"🟫","Silver":"⚪","Gold":"🟡","Platinum":"🟩","Diamond":"💎","Ruby":"❤️"}.get(tier_name.split()[0], "")

def fetch_solved_meta(pid: int, max_tags: int, tier_emoji: bool) -> Optional[Dict[str, Any]]:
    data = http_get_json(SOLVED_SHOW.format(pid=pid))
    if not data or "problemId" not in data: return None
    tier = level_to_name(data.get("level"))
    if tier_emoji and tier:
        icon = tier_icon(tier)
        if icon: tier = f"{icon} {tier}"
    tags: List[str] = []
    for t in data.get("tags", []):
        ko = next((d.get("name") for d in t.get("displayNames", []) if d.get("language")=="ko"), None)
        tags.append((ko or t.get("key") or "").strip())
    tags = [x for x in sorted(tags) if x][:max_tags]
    return {
        "tier": tier,
        "solved_count": data.get("solvedUserCount") or data.get("acceptedUserCount"),
        "average_tries": data.get("averageTries"),
        "is_solvable": data.get("isSolvable"),
        "tags": tags,
    }

# ─────────────────────────────────────────────────────────────────────────────
# File utils & templates
# ─────────────────────────────────────────────────────────────────────────────
def ensure_dir(p: Path) -> None:
    p.mkdir(parents=True, exist_ok=True)

def safe_write(path: Path, content: str, *, force: bool, label: str) -> str:
    """
    파일 쓰기(UTF-8). 반환: 'created' | 'overwritten' | 'skipped'
    """
    if path.exists():
        if force:
            path.write_text(content, encoding="utf-8")
            print(f"↻ 덮어씀: {label} → {path}")
            return "overwritten"
        else:
            print(f"⏭  건너뜀(존재함): {label} → {path}")
            return "skipped"
    else:
        path.write_text(content, encoding="utf-8")
        print(f"＋ 생성: {label} → {path}")
        return "created"

def build_meta_lines(pid: int, boj: dict, solved: Optional[dict]) -> List[str]:
    lines = [f"{pid} – {boj.get('title','')}",
             f"https://www.acmicpc.net/problem/{pid}",
             f"solved.ac: https://solved.ac/search?query={pid}"]
    if boj.get("time_limit"):   lines.append(f"시간 제한: {boj['time_limit']}")
    if boj.get("memory_limit"): lines.append(f"메모리 제한: {boj['memory_limit']}")
    if solved:
        if solved.get("tier"): lines.append(f"티어: {solved['tier']}")
        if solved.get("tags"): lines.append("태그: " + ", ".join(solved["tags"]))
        if solved.get("solved_count") is not None: lines.append(f"푼 사람 수: {solved['solved_count']:,}")
        if solved.get("average_tries") is not None: lines.append(f"평균 시도: {solved['average_tries']:.2f}")
    return lines

def comment_block(lang: str, lines: List[str]) -> str:
    prefix = "# " if lang=="py" else "// "
    return "\n".join(prefix + l for l in lines) + "\n\n"

def body_cpp() -> str:
    return """#include <iostream>
#if defined(_WIN32)
  #include <io.h>
  #include <cstdio>
#else
  #include <unistd.h>
  #include <cstdio>
#endif

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 표준입력이 터미널이면 input.txt로 대체 (파이프 입력 시에는 그대로 cin)
#if defined(_WIN32)
    if (_isatty(_fileno(stdin))) { freopen("input.txt", "r", stdin); }
#else
    if (isatty(fileno(stdin))) { freopen("input.txt", "r", stdin); }
#endif

    int N, M;
    if (!(cin >> N >> M)) return 0;
    cout << "N: " << N << " M: " << M << "\\n";
    return 0;
}
"""

def body_py() -> str:
    return """import sys, io

def input_stream():
    try:
        if not sys.stdin.isatty():
            return io.TextIOWrapper(sys.stdin.buffer, encoding="utf-8", newline="")
    except Exception:
        pass
    try:
        return open("input.txt", "r", encoding="utf-8", newline="")
    except FileNotFoundError:
        return io.TextIOWrapper(sys.stdin.buffer, encoding="utf-8", newline="")

def main() -> None:
    f = input_stream()
    line = f.readline().strip()
    if not line:
        return
    N, M = map(int, line.split())
    print(f"N: {N} M: {M}")

if __name__ == "__main__":
    main()
"""

def body_java() -> str:
    return """import java.io.*;
import java.util.*;
import java.nio.charset.StandardCharsets;

// public class Main {
class Main {
    public static void main(String[] args) throws Exception {
        InputStream in = System.in;
        try {
            // 파이프된 입력이 없고 input.txt가 있으면 그것으로 전환
            if (in.available() == 0) {
                File f = new File("input.txt");
                if (f.exists()) in = new FileInputStream(f);
            }
        } catch (Exception ignored) {}

        BufferedReader br = new BufferedReader(new InputStreamReader(in, StandardCharsets.UTF_8));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());
        System.out.println("N: " + N + " M: " + M);
    }
}
"""

def generate_source(lang: str, boj: dict, solved: Optional[dict]) -> str:
    header = comment_block(lang, build_meta_lines(int(boj.get('id', 0)) or 0, boj, solved))
    return header + (body_cpp() if lang=="cpp" else body_py() if lang=="py" else body_java())

def make_vscode_ccpp() -> str:
    return """{
  "configurations": [
    {
      "name": "Win64",
      "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "windowsSdkVersion": "10.0.22621.0",
            "compilerPath": "C:/msys64/ucrt64/bin/g++.exe",
            "cStandard": "c99",
            "cppStandard": "c++14",
            "intelliSenseMode": "windows-gcc-x64",
            "configurationProvider": "ms-vscode.cpptools"
        }
    ],
    "version": 4
}
"""

def make_run_sh() -> str:
    return r"""#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")"
shopt -s nullglob

# ─────────────────────────────────────────────────────────────
# 0) 공통 유틸
#   - unixify: CRLF→LF 정규화 + 마지막 줄 개행(LF) 보장
#     (gawk의 RS/RT를 이용해 EOF 개행 유무를 정확히 처리)
# ─────────────────────────────────────────────────────────────
unixify() {
  gawk 'BEGIN{RS="\r?\n"; ORS=""}
       { printf "%s", $0; if (RT!="") printf "\n" }
       END { if (NR>0 && RT=="") printf "\n" }'
}
have() { command -v "$1" >/dev/null 2>&1; }

# ─────────────────────────────────────────────────────────────
# 1) 소스 선택
# ─────────────────────────────────────────────────────────────
pick="${1:-}"
cands=( *.cpp *.py *.java )
if [[ -z "${pick}" ]]; then
  if [[ ${#cands[@]} -eq 0 ]]; then
    echo "소스 파일이 없습니다."; exit 1
  fi
  echo "🔎 실행할 소스 선택:"
  select pick in "${cands[@]}"; do
    [[ -n "${pick:-}" ]] && break
  done
fi
[[ -f "$pick" ]] || { echo "유효한 소스 파일이 아닙니다: $pick"; exit 1; }

# ─────────────────────────────────────────────────────────────
# 2) C++이면 UCRT64로 재실행(bounce)
#    (이미 UCRT64면 그대로 진행)
# ─────────────────────────────────────────────────────────────
ext="${pick##*.}"
MSYS_NOW="${MSYSTEM:-}"
if [[ "$ext" == "cpp" && "$MSYS_NOW" != "UCRT64" ]]; then
  PICK_FILE="$(mktemp -t run_pick.XXXXXX)"
  printf '%s' "$pick" > "$PICK_FILE"
  trap 'rm -f "$PICK_FILE"' EXIT

  UCRT_BASH="/c/msys64/usr/bin/bash.exe"
  UCRT_ENV="/c/msys64/usr/bin/env.exe"

  if [[ -x "$UCRT_BASH" && -x "$UCRT_ENV" ]]; then
    echo "↪ UCRT64로 재실행(bash.exe -lc)"
    exec "$UCRT_ENV" MSYSTEM=UCRT64 CHERE_INVOKING=1 \
         "$UCRT_BASH" -lc "cd \"$PWD\"; p=\$(cat \"$PICK_FILE\"); rm -f \"$PICK_FILE\"; bash ./run.sh \"\$p\""
  else
    echo "❗ UCRT bash를 찾을 수 없습니다: $UCRT_BASH (또는 env.exe)"
    exit 1
  fi
fi

# ─────────────────────────────────────────────────────────────
# 3) 입력 파일 목록
# ─────────────────────────────────────────────────────────────
inputs=( tests/*.in )
if [[ ${#inputs[@]} -eq 0 ]]; then
  inputs=( input.txt )
fi

mkdir -p out

# ─────────────────────────────────────────────────────────────
# 4) 언어별 빌드/실행 커맨드 준비
# ─────────────────────────────────────────────────────────────
run_cmd() { :; }  # placeholder
case "$ext" in
  cpp)
    gpp="C:/msys64/ucrt64/bin/g++.exe"
    [[ -x "$gpp" ]] || gpp="g++"
    exe="./main.exe"
    echo "⚙️  compile: $pick -> $exe"
    "$gpp" "$pick" -std=c++14 -O2 -pipe -static -s -o "$exe"
    run_cmd() { ./main.exe; }
    ;;
  py)
    run_cmd() { python -X utf8 "$pick"; }
    ;;
  java)
    # 임시 빌드 디렉터리(지정 없으면 자동 삭제)
    JAVA_BUILD_DIR="${JAVA_BUILD_DIR:-}"
    if [[ -z "$JAVA_BUILD_DIR" ]]; then
      build_dir="$(mktemp -d)"
      CLEAN_BUILD=1
    else
      build_dir="$JAVA_BUILD_DIR"
      mkdir -p "$build_dir"
      CLEAN_BUILD=0
    fi
    trap '[[ "${CLEAN_BUILD:-0}" == "1" ]] && rm -rf "$build_dir"' EXIT

    echo "⚙️  javac -encoding UTF-8 -d \"$build_dir\" $pick"
    javac -encoding UTF-8 -d "$build_dir" "$pick"

    run_cmd() { java -Dfile.encoding=UTF-8 -cp "$build_dir" Main; }
    ;;
  *)
    echo "알 수 없는 확장자: $pick"; exit 1 ;;
esac

# ─────────────────────────────────────────────────────────────
# 5) 실행 & 검증 (CR/LF 정규화, diff 없으면 cmp fallback)
# ─────────────────────────────────────────────────────────────
for in_file in "${inputs[@]}"; do
  tmp_out="$(mktemp)"
  out_file="out/$(basename "$pick").$(basename "$in_file").out"
  echo "▶ $pick < $(basename "$in_file")"
  run_cmd < "$in_file" > "$tmp_out" || true

  exp=""
  if [[ "$in_file" == tests/*.in ]]; then
    exp="${in_file%.in}.out"
  fi

  if [[ -n "$exp" && -f "$exp" ]]; then
    if have diff; then
      if diff -u <(unixify < "$exp") <(unixify < "$tmp_out") > /dev/null; then
        echo "✅ PASS"
      else
        echo "❌ FAIL"
        diff -u <(unixify < "$exp") <(unixify < "$tmp_out") || true
      fi
    else
      exp_u="$(mktemp)"; tmp_u="$(mktemp)"
      unixify < "$exp" > "$exp_u"
      unixify < "$tmp_out" > "$tmp_u"
      if cmp -s "$exp_u" "$tmp_u"; then
        echo "✅ PASS (cmp)"
      else
        echo "❌ FAIL (cmp) — 시스템에 diff가 없어 상세 비교는 생략"
        echo "---- expected (head) ----"; head -n 40 "$exp_u" || true
        echo "---- actual   (head) ----"; head -n 40 "$tmp_u" || true
        echo "-------------------------"
      fi
      rm -f "$exp_u" "$tmp_u"
    fi
  else
    echo "ℹ️  비교용 정답 파일 없음"
  fi

  mv -f "$tmp_out" "$out_file"
done
"""

def open_vscode() -> bool:
    for exe in ("code.cmd", "code"):
        if shutil.which(exe):
            try:
                subprocess.Popen([exe, "."], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
                return True
            except Exception:
                pass
    return False

# ─────────────────────────────────────────────────────────────────────────────
# Main
# ─────────────────────────────────────────────────────────────────────────────
def main() -> None:
    args = parse_args()
    lang = normalize_lang(args.lang)
    pid = args.id or infer_id_from_dir()
    if not pid:
        print("❗ 폴더명에서 문제 번호를 찾지 못했습니다. --id <번호> 를 지정하세요.", file=sys.stderr)
        sys.exit(1)

    # BOJ
    url = BOJ_BASE + str(pid)
    html = http_get_text(url, verify=not args.insecure, debug=args.debug)
    boj_meta = parse_problem(html)
    boj_meta["id"] = pid
    if not boj_meta["title"]:
        print("❗ 제목 파싱 실패", file=sys.stderr); sys.exit(2)
    print(f"▶ 제목: {boj_meta['title']}")
    if boj_meta.get("time_limit") or boj_meta.get("memory_limit"):
        print(f"   (시간: {boj_meta.get('time_limit')}, 메모리: {boj_meta.get('memory_limit')})")

    # solved.ac (실패해도 계속)
    solved_meta: Optional[dict] = None
    if not args.no_solvedac:
        try:
            solved_meta = fetch_solved_meta(pid, max_tags=args.max_tags, tier_emoji=args.tier_emoji)
            if solved_meta and solved_meta.get("tier"):
                preview_tags = ", ".join(solved_meta.get("tags", [])[:5])
                print(f"   (티어: {solved_meta['tier']}" + (f", 태그: {preview_tags}" if preview_tags else "") + ")")
        except Exception:
            solved_meta = None

    # 지정경로 해석
    try:
        dest_parent = resolve_dest_path(args)
    except ValueError as e:
        print(f"❗ {e}", file=sys.stderr); sys.exit(4)

    # 경로/파일명 결정
    if dest_parent:
        dir_title = sanitize_title_for_dir(boj_meta["title"])
        folder_name = f"{pid}.{dir_title}"
        target_dir = make_problem_folder(dest_parent, folder_name)
        os.chdir(target_dir)
        print(f"📂 작업 폴더: {target_dir}")
        file_base = folder_name
        if lang == "cpp":   src_path = Path(f"{file_base}.cpp")
        elif lang == "py":  src_path = Path(f"{file_base}.py")
        else:               src_path = Path(f"{file_base}.java")
    else:
        base = unified_basename(args.username, pid)
        if lang == "cpp":   src_path = Path(f"{base}.cpp")
        elif lang == "py":  src_path = Path(f"{base}.py")
        else:               src_path = Path(f"{base}.java")

    # tests/ 및 input.txt (개별 파일 단위로 skip/force)
    tests_dir = Path("tests"); ensure_dir(tests_dir)
    samples = boj_meta["samples"]

    if not samples:
        safe_write(Path("input.txt"), "", force=args.force, label="input.txt")
        print("⚠️ 샘플 미발견 → 빈 input.txt 유지/생성")
    else:
        # input.txt = 첫 샘플 입력
        safe_write(Path("input.txt"), samples[0][0], force=args.force, label="input.txt")
        # sample*.in/out
        for i, (iin, oout) in enumerate(samples, 1):
            safe_write(tests_dir / f"sample{i}.in", iin, force=args.force, label=f"tests/sample{i}.in")
            if oout.strip():
                safe_write(tests_dir / f"sample{i}.out", oout, force=args.force, label=f"tests/sample{i}.out")

    # 소스 생성 (메타 주석 헤더 포함)
    source_text = generate_source(lang, boj_meta, solved_meta)
    _src_status = safe_write(src_path, source_text, force=args.force, label=src_path.name)

    # VSCode C++ 설정
    if lang == "cpp":
        vscode_dir = Path(".vscode"); ensure_dir(vscode_dir)
        cprop = vscode_dir / "c_cpp_properties.json"
        safe_write(cprop, make_vscode_ccpp(), force=args.force, label=str(cprop))

    # run.sh 생성(언어 공통)
    run_sh = Path("run.sh")
    safe_write(run_sh, make_run_sh(), force=args.force, label="run.sh")
    try:
        os.chmod(run_sh, 0o755)
    except Exception:
        pass

    print(f"✅ 완료 (생성/갱신) → {src_path}  tests/  input.txt  run.sh")

    # VS Code 열기
    if open_vscode(): print("🟦 VS Code 열기: 완료")
    else:             print("ℹ️ VS Code 실행 파일(code) 미검출 — 수동으로 열어 주세요.")

    # 즉시 실행 (--run) → 방금 만든(또는 기존) 소스 지정하여 run.sh 호출
    if args.run:
        pick_name = src_path.name
        cmd = f'./run.sh "{pick_name}"' if os.name != "nt" else f'bash ./run.sh "{pick_name}"'
        print(f"▶ 실행: {cmd}")
        os.system(cmd)

if __name__ == "__main__":
    main()
