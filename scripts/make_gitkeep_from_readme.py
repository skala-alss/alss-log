#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from __future__ import annotations
import argparse
import re
import sys
from pathlib import Path, PurePosixPath
from urllib.parse import unquote

# ✅ 더 관대한 패턴들
MD_LINK_RE   = re.compile(r"\[([^\]]+)\]\s*\(([^)]+)\)")
HTML_LINK_RE = re.compile(r'<a\s+[^>]*href="([^"]+)"[^>]*>(.*?)</a>', re.IGNORECASE | re.DOTALL)

WIN_INVALID_CHARS = set('<>:"/\\|?*')
WIN_RESERVED = {
    "CON", "PRN", "AUX", "NUL",
    *{f"COM{i}" for i in range(1, 10)},
    *{f"LPT{i}" for i in range(1, 10)},
}

def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="README의 [📁](상대경로) 또는 <a href>📁 링크를 파싱해 폴더/.gitkeep 생성")
    default_readme = Path(__file__).resolve().parent.parent / "week04" / "README.md"
    p.add_argument("--readme", type=Path, default=default_readme, help=f"파싱할 README 경로 (기본: {default_readme})")
    p.add_argument("--dry-run", action="store_true", help="생성하지 않고 점검만")
    p.add_argument("--verbose", "-v", action="count", default=0, help="매칭/필터 로그 출력")
    return p.parse_args()

def extract_links(md: str, verbose: int = 0) -> list[str]:
    links = []

    # 1) Markdown 링크: [텍스트](URL) 중 텍스트에 📁 포함
    for text, url in MD_LINK_RE.findall(md):
        if "📁" in text:
            links.append(url.strip())

    # 2) HTML 앵커: <a href="URL"> ... 📁 ... </a>
    for url, inner in HTML_LINK_RE.findall(md):
        if "📁" in inner:
            links.append(url.strip())

    # URL 디코드 + 상대경로만
    links = [unquote(l) for l in links if not ("://" in l or l.startswith(("http:", "https:")))]

    # 중복 제거
    uniq = []
    seen = set()
    for l in links:
        if l not in seen:
            uniq.append(l)
            seen.add(l)

    if verbose:
        print(f"[debug] raw-matches={len(links)} (uniq={len(uniq)})")
        for i, l in enumerate(uniq[:10], 1):
            print(f"  {i:02d}. {l}")
    return uniq

def to_abs_paths(readme_path: Path, rel_links: list[str]) -> list[Path]:
    base = readme_path.parent.resolve()  # ✅ 절대경로로 고정
    print(f"[debug] base={base}")  # 절대경로인지 확인
    out = []
    for link in rel_links:
        posix = PurePosixPath(link)
        abs_p = (base / Path(*posix.parts)).resolve()
        try:
            abs_p.relative_to(base)
        except ValueError:
            # base 밖으로 나가는 상대경로는 제외
            continue
        out.append(abs_p)
    return sorted(set(out))

def check_windows_name_issues(base: Path, targets: list[Path]):
    base = base.resolve()
    problems = []
    for p in targets:
        try:
            rel_parts = p.resolve().relative_to(base).parts
        except ValueError:
            # 이 경우는 base 밖인데, 어차피 to_abs_paths에서 거른 상태라 거의 없음
            rel_parts = p.resolve().parts

        for part in rel_parts:
            if not part:
                continue

            # ✅ Windows 드라이브/앵커는 건너뜀 (예: 'C:\' 또는 'D:')
            #  - Path.parts에선 'C:\\' 꼴이 나올 수 있음
            if re.fullmatch(r"[A-Za-z]:\\?", part):
                continue

            if part.endswith(" ") or part.endswith("."):
                problems.append((p, f"끝 공백/점 포함: '{part}'"))
                break

            # ✅ 예약어(CON.txt 등)도 막기: 확장자를 떼고 비교
            name_no_ext = part.split(".")[0].upper()
            if name_no_ext in WIN_RESERVED:
                problems.append((p, f"예약어 이름: '{part}'"))
                break

            bad = [c for c in part if c in WIN_INVALID_CHARS]
            if bad:
                problems.append((p, f"금지 문자 포함({''.join(sorted(set(bad)))}): '{part}'"))
                break
    return problems

def main():
    args = parse_args()
    readme = args.readme

    if not readme.exists():
        print(f"❌ README를 찾을 수 없습니다: {readme}", file=sys.stderr)
        sys.exit(2)

    md = readme.read_text(encoding="utf-8", errors="ignore")
    rel_links = extract_links(md, verbose=args.verbose)
    if not rel_links:
        print("⚠️ README에서 폴더 링크(📁)를 찾지 못했습니다. (-v로 원문 매칭 로그 확인)")
        sys.exit(0)

    targets = to_abs_paths(readme, rel_links)

    # ✅ base를 반드시 resolve해서 사용
    base = readme.parent.resolve()
    name_issues = check_windows_name_issues(base, targets)
    if name_issues:
        print("⚠️ Windows 금지 이름/문자 감지. 생성 작업을 중단합니다.\n")
        for p, why in name_issues:
            print(f" - {p}  ← {why}")
        sys.exit(1)

    if args.dry_run or args.verbose:
        print("📝 생성 대상 폴더 목록:")
        for p in targets:
            print(f" - {p}")
        print(f"총 {len(targets)}개 (README: {readme})")
        if args.dry_run:
            return

    touched = 0
    for d in targets:
        d.mkdir(parents=True, exist_ok=True)
        gk = d / ".gitkeep"
        if not gk.exists():
            gk.touch()
            touched += 1

    print(f"✅ 완료: 대상 {len(targets)}개")
    print(f"   ├─ 폴더 확인/생성: {len(targets)}개")
    print(f"   └─ .gitkeep 생성: {touched}개 (기존 존재 제외)")
    print(f"📄 기준 README: {readme}")

if __name__ == "__main__":
    main()
