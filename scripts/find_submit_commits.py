#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
find_submit_commits.py (robust, grep-less, all-refs)

- 모든 로컬 refs(--all)에서 커밋을 읽어 'submit: week{번호}-{이름}' 패턴을 NFKC 정규화 후 탐지.
- 이모지, 전각 콜론(：), 대괄호 변종 'submit] week..', 엔대시(–/—), 공백·언더스코어 구분 허용.
- Git 출력은 UTF-8로 강제하고, 레코드/필드를 RS(0x1E)/US(0x1F)로 구분해 안전 파싱.

옵션:
  --main-only         origin/main(or main/HEAD)만 스캔
  --ref REF           특정 ref만 (반복 지정 가능, --all/--main-only와 병행 X)
  --since / --until   기간 필터 (YYYY-MM-DD)
  --week              3 또는 03
  --name              alias (대소문자 무시)
  --limit N           로그 상한
  --files             변경 파일 표시
  --show-refs         커밋을 포함하는 브랜치/리모트 ref 표시
  --json              JSON 출력
  --debug             매칭 실패 시 샘플 주제 출력
"""
import argparse, subprocess, shlex, re, json, sys, datetime, unicodedata
from typing import List, Dict, Any, Optional

RS = "\x1e"  # record separator
US = "\x1f"  # unit separator

# submit[:|]|： week 03 - name  (대시/스페이스/언더스코어/엔대시/엠대시 허용)
SUBMIT_RE = re.compile(
    r"""submit\s*[:\]\uff1a]?\s*week\s*0*([0-9]{1,2})\s*[-–—_ ]\s*([A-Za-z0-9_\-]+)""",
    re.IGNORECASE | re.VERBOSE,
)
PR_NUM_RE = re.compile(r"\(#\s*(\d+)\s*\)")

def run_git_bytes(cmd: str) -> bytes:
    # Windows 인코딩 이슈 회피: 바이트로 받고 UTF-8 우선
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    out, _ = p.communicate()
    return out or b""

def git_log_cmd(scan_all: bool, refs: Optional[List[str]], since: Optional[str], until: Optional[str], limit: Optional[int]) -> str:
    parts = [
        "git", "-c", "core.quotepath=off",
        "-c", "i18n.logOutputEncoding=UTF-8",
        "log", "--no-color"
    ]
    if limit and limit > 0:
        parts += ["-n", str(limit)]
    # ✅ 제어문자는 직접 박지 말고 %x 이스케이프 사용
    parts += ["--pretty=format:%H%x1f%ct%x1f%s%x1e"]
    if since:
        parts += [f"--since={since}"]
    if until:
        parts += [f"--until={until}"]
    if scan_all:
        parts += ["--all"]
    else:
        final_refs = refs if refs else resolve_default_refs_main_only()
        parts += final_refs
    # shell=True를 쓰고 있으니 공백/인수들을 안전하게 합치기
    return " ".join(shlex.quote(x) for x in parts)

def resolve_default_refs_main_only() -> List[str]:
    for ref in ["origin/main", "main", "HEAD"]:
        try:
            subprocess.check_output(f"git rev-parse --verify {shlex.quote(ref)}", shell=True, stderr=subprocess.DEVNULL)
            return [ref]
        except Exception:
            continue
    return ["HEAD"]

def to_kst(ts: int) -> str:
    try:
        from zoneinfo import ZoneInfo
        dt = datetime.datetime.utcfromtimestamp(ts).replace(tzinfo=datetime.timezone.utc).astimezone(ZoneInfo("Asia/Seoul"))
    except Exception:
        dt = datetime.datetime.utcfromtimestamp(ts) + datetime.timedelta(hours=9)
    return dt.strftime("%Y-%m-%d %H:%M")

def parse_record(rec: str) -> Optional[Dict[str, Any]]:
    if not rec:
        return None
    parts = rec.split(US)
    if len(parts) < 3:
        return None
    sha, ts_s, subj = parts[0].strip(), parts[1].strip(), parts[2].strip()
    try:
        ts = int(ts_s)
    except Exception:
        ts = 0
    # 정규화 후 패턴 매칭
    subj_norm = unicodedata.normalize("NFKC", subj)
    m = SUBMIT_RE.search(subj_norm)
    if not m:
        return None
    wk = f"{int(m.group(1)):02d}"
    alias = m.group(2)
    mm = PR_NUM_RE.search(subj_norm)
    pr = int(mm.group(1)) if mm else None
    return {
        "sha": sha,
        "short": sha[:7],
        "timestamp": ts,
        "date_kst": to_kst(ts),
        "week": wk,
        "name": alias,
        "subject": subj_norm,
        "pr": pr,
    }

def list_files(sha: str) -> List[str]:
    cmd = f"git -c core.quotepath=off show --name-only --no-renames --pretty= {shlex.quote(sha)}"
    out = run_git_bytes(cmd)
    text = None
    for enc in ("utf-8", "cp949", "euc-kr", "latin-1"):
        try:
            text = out.decode(enc)
            break
        except Exception:
            continue
    if text is None:
        text = out.decode("utf-8", errors="replace")
    return [ln.strip() for ln in text.splitlines() if ln.strip()]

def list_containing_refs(sha: str) -> List[str]:
    cmd = (
        "git for-each-ref --format='%(refname:short)' "
        f"--contains {shlex.quote(sha)} refs/heads refs/remotes"
    )
    out = run_git_bytes(cmd)
    text = out.decode("utf-8", errors="replace")
    return [ln.strip().strip("'") for ln in text.splitlines() if ln.strip()]

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--main-only", action="store_true")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--ref", action="append")
    ap.add_argument("--since"); ap.add_argument("--until")
    ap.add_argument("--week"); ap.add_argument("--name")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--files", action="store_true")
    ap.add_argument("--show-refs", action="store_true")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--debug", action="store_true")
    args = ap.parse_args()

    # 스캔 범위
    if args.ref:
        scan_all, refs = False, args.ref
    else:
        scan_all = True if (args.all or not args.main_only) else False
        refs = None

    # 로그 취득 (바이트) → 다중 인코딩 시도
    cmd = git_log_cmd(scan_all, refs, args.since, args.until, args.limit)
    raw = run_git_bytes(cmd)
    text = None
    for enc in ("utf-8", "cp949", "euc-kr", "latin-1"):
        try:
            text = raw.decode(enc)
            break
        except Exception:
            continue
    if text is None:
        text = raw.decode("utf-8", errors="replace")

    items: List[Dict[str, Any]] = []
    seen = set()

    # RS(레코드) 단위 분해
    for rec in text.split(RS):
        item = parse_record(rec)
        if not item:
            continue
        if args.week:
            try:
                target = f"{int(args.week):02d}"
            except Exception:
                target = args.week.zfill(2)
            if item["week"] != target:
                continue
        if args.name and item["name"].lower() != args.name.lower():
            continue
        if item["sha"] in seen:
            continue
        seen.add(item["sha"])
        if args.files:
            item["files"] = list_files(item["sha"])
        if args.show_refs:
            item["refs"] = list_containing_refs(item["sha"])
        items.append(item)

    items.sort(key=lambda x: (x["timestamp"], x["sha"]), reverse=True)

    if args.json:
        print(json.dumps(items, ensure_ascii=False, indent=2)); return

    if not items:
        print("(no matching commits)")
        if args.debug:
            # 매칭 실패 디버그: 'submit' 단어가 들어간 subject 샘플 10건 출력
            subs = []
            for rec in text.split(RS):
                parts = rec.split(US)
                if len(parts) >= 3:
                    subj = unicodedata.normalize("NFKC", parts[2].strip())
                    if "submit" in subj.lower():
                        subs.append(subj)
                if len(subs) >= 10:
                    break
            if subs:
                print("\n[debug] subjects containing 'submit' sample:")
                for s in subs:
                    print(" -", s)
        return

    extra = " REFS" if args.show_refs else ""
    print(f"{'DATE(KST)':<16} {'WEEK':<4} {'NAME':<16} {'PR':<6} {'SHA':<8} SUBJECT{extra}")
    print("-"*16, "-"*4, "-"*16, "-"*6, "-"*8, "-"*40, "--------------------" if args.show_refs else "")

    for r in items:
        pr = f"#{r['pr']}" if r.get("pr") else "-"
        line = f"{r['date_kst']:<16} {r['week']:<4} {r['name']:<16} {pr:<6} {r['short']:<8} {r['subject']}"
        if args.show_refs:
            refs = ", ".join(r.get("refs", [])) or "-"
            line += f" {refs}"
        print(line)

if __name__ == "__main__":
    main()
