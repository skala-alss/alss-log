#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from __future__ import annotations
import argparse
import re
import sys
import unicodedata
from pathlib import Path, PurePosixPath
from urllib.parse import unquote

# ─────────────────────────────────────────────────────────────────────────────
# 링크 패턴
#  - Markdown: 중첩 괄호 1단계 + 이스케이프 + (<...>) 형식 지원
# ─────────────────────────────────────────────────────────────────────────────
MD_LINK_RE = re.compile(
    r"""
    \[([^\]]+)\]          # [링크텍스트]
    \s*
    \(
      \s*
      (                   # ← URL 캡처
        (?:
            <[^>]*>                 # <...> 로 감싼 URL
          | (?:[^()\\]|\\.)+        # 일반 문자 또는 이스케이프된 문자
          | \([^()]*\)              # 한 단계 중첩 괄호 허용
        )+
      )
      \s*
    \)
    """,
    re.VERBOSE,
)
HTML_LINK_RE = re.compile(r'<a\s+[^>]*href="([^"]+)"[^>]*>(.*?)</a>', re.IGNORECASE | re.DOTALL)

# ─────────────────────────────────────────────────────────────────────────────
# 금지문자/예약어/유령문자 처리 (BOJ 크롤러 정책 반영: 전각 치환)
# ─────────────────────────────────────────────────────────────────────────────
_FORBID_MAP = {"/":"／","\\":"＼","?":"？",":":"：","*":"＊","\"":"＂","<":"＜",">":"＞","|":"｜"}
_RESERVED_WIN = re.compile(r"^(CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])$", re.IGNORECASE)
_ZWS_RE = re.compile(r"[\u200B\u200C\u200D\uFEFF]")  # ZWSP/ZWJ/ZWNJ/BOM

# (로그용) 기존 검사 집합
WIN_INVALID_CHARS = set('<>:"/\\|?*')
WIN_RESERVED_SET = {
    "CON", "PRN", "AUX", "NUL",
    *{f"COM{i}" for i in range(1, 10)},
    *{f"LPT{i}" for i in range(1, 10)},
}

# ─────────────────────────────────────────────────────────────────────────────
# CLI
# ─────────────────────────────────────────────────────────────────────────────
def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="README의 [📁](상대경로) 또는 <a href>📁 링크를 파싱해 폴더/.gitkeep 생성")
    default_readme = Path(__file__).resolve().parent.parent / "week04" / "README.md"
    p.add_argument("--readme", type=Path, default=default_readme, help=f"파싱할 README 경로 (기본: {default_readme})")
    p.add_argument("--dry-run", action="store_true", help="생성하지 않고 점검만")
    p.add_argument("--verbose", "-v", action="count", default=0, help="매칭/필터/치환 로그 출력")
    return p.parse_args()

# ─────────────────────────────────────────────────────────────────────────────
# 문자열 정규화 유틸
# ─────────────────────────────────────────────────────────────────────────────
def _strip_invisibles(s: str) -> str:
    # NBSP→space, ZWSP/ZWJ/ZWNJ/BOM 제거, NFC 정규화
    s = _ZWS_RE.sub("", (s or "").replace("\xa0", " "))
    try:
        s = unicodedata.normalize("NFC", s)
    except Exception:
        pass
    return s

def sanitize_component_keep_spaces(part: str) -> str:
    """
    폴더/파일 컴포넌트용 안전화:
      - 제어문자 제거
      - 금지문자 전각 치환 (BOJ 크롤러와 동일 맵)
      - 후행 공백/점 제거 + 선행 점 제거
      - 확장자 제외 본체가 예약어면 '_' 접두
      - 공백은 유지(README 상대경로와 동기화 목적)
    """
    s = _strip_invisibles(part or "")
    # 제어문자 제거
    s = "".join(ch for ch in s if ord(ch) >= 32)
    # 전각 치환
    for k, v in _FORBID_MAP.items():
        s = s.replace(k, v)
    # 끝 공백/점 제거 + 선행 점 제거
    s = s.rstrip(" .")
    s = re.sub(r"^\.+", "", s)
    # 예약어 보호 (확장자 제외 본체 기준)
    stem = (s.split(".", 1)[0]).upper()
    if _RESERVED_WIN.match(stem):
        s = "_" + s
    return s or "_"

# ─────────────────────────────────────────────────────────────────────────────
# 링크 추출/정규화
# ─────────────────────────────────────────────────────────────────────────────
def extract_links(md: str, verbose: int = 0) -> list[str]:
    links: list[str] = []

    # 1) Markdown: [텍스트](URL) – 텍스트에 📁 포함
    for text, url in MD_LINK_RE.findall(md):
        if "📁" in text:
            url = url.strip()
            # (<...>)로 감싼 URL이면 벗겨냄
            if url.startswith("<") and url.endswith(">"):
                url = url[1:-1].strip()
            links.append(url)

    # 2) HTML 앵커: <a href="URL"> ... 📁 ... </a>
    for url, inner in HTML_LINK_RE.findall(md):
        if "📁" in inner:
            links.append(url.strip())

    # URL 디코드 + 외부URL 제외 + 보이지 않는 문자 제거 + 트레일링 슬래시 제거
    links = [
        _strip_invisibles(unquote(l)).rstrip("/")
        for l in links
        if not ("://" in l or l.startswith(("http:", "https:")))
    ]

    # 중복 제거(정규화된 문자열 기준)
    uniq, seen = [], set()
    for l in links:
        if l not in seen:
            uniq.append(l); seen.add(l)

    if verbose:
        print(f"[debug] raw-matches={len(links)} (uniq={len(uniq)})")
        for i, l in enumerate(uniq[:20], 1):
            print(f"  {i:02d}. {l}")
    return uniq

# ─────────────────────────────────────────────────────────────────────────────
# 안전 경로 빌드 & base 탈출 방지
# ─────────────────────────────────────────────────────────────────────────────
def build_safe_path(base: Path, posix_parts: tuple[str, ...]) -> Path:
    """
    PurePosixPath(parts) → 각 part를 sanitize하여 OS 경로로 재조립.
    '.'은 무시, '..'은 우선 포함하되 최종 relative_to(base) 검증에서 필터.
    """
    p = base
    for part in posix_parts:
        if part in ("", "."):
            continue
        if part == "..":
            p = p / part
            continue
        p = p / sanitize_component_keep_spaces(part)
    return p

def to_abs_paths(readme_path: Path, rel_links: list[str]) -> list[Path]:
    base = readme_path.parent.resolve()
    out: list[Path] = []
    for link in rel_links:
        posix = PurePosixPath(link)  # 입력은 POSIX 기준으로 해석
        abs_p = build_safe_path(base, posix.parts).resolve()
        try:
            abs_p.relative_to(base)  # base 밖으로 나가면 ValueError
        except ValueError:
            continue
        out.append(abs_p)
    # 중복 제거 + 정렬
    return sorted(set(out))

# ─────────────────────────────────────────────────────────────────────────────
# 검사 로직(로그용) — 생성 중단하지 않음
# ─────────────────────────────────────────────────────────────────────────────
def check_windows_name_issues(base: Path, targets: list[Path]):
    base = base.resolve()
    problems = []
    for p in targets:
        try:
            rel_parts = p.resolve().relative_to(base).parts
        except ValueError:
            rel_parts = p.resolve().parts

        for part in rel_parts:
            if not part:
                continue
            # 드라이브 앵커 패스
            if re.fullmatch(r"[A-Za-z]:\\?", part):
                continue
            if part.endswith(" ") or part.endswith("."):
                problems.append((p, f"끝 공백/점 포함: '{part}'"))
                break

            name_no_ext = part.split(".", 1)[0].upper()
            if name_no_ext in WIN_RESERVED_SET:
                problems.append((p, f"예약어 이름: '{part}'"))
                break

            bad = [c for c in part if c in WIN_INVALID_CHARS]
            if bad:
                problems.append((p, f"금지 문자 포함({''.join(sorted(set(bad)))}): '{part}'"))
                break
    return problems

# ─────────────────────────────────────────────────────────────────────────────
# 매핑 미리보기
# ─────────────────────────────────────────────────────────────────────────────
def preview_mapping(base: Path, rel_links: list[str]):
    for link in rel_links:
        posix = PurePosixPath(link)
        raw = (base / Path(*posix.parts))
        sanitized = build_safe_path(base, posix.parts)
        try:
            raw_rel = raw.resolve().relative_to(base)
        except Exception:
            raw_rel = raw
        try:
            san_rel = sanitized.resolve().relative_to(base)
        except Exception:
            san_rel = sanitized
        if str(raw_rel) != str(san_rel):
            print(f"  map: {link}  →  {san_rel}")

# ─────────────────────────────────────────────────────────────────────────────
# 메인
# ─────────────────────────────────────────────────────────────────────────────
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

    base = readme.parent.resolve()
    if args.verbose:
        print(f"[debug] base={base}")
        print("🧪 경로 치환 미리보기:")
        preview_mapping(base, rel_links)

    targets = to_abs_paths(readme, rel_links)

    # 검사: 경고만 출력하고 계속 진행 (치환 규칙이 이미 반영됨)
    name_issues = check_windows_name_issues(base, targets)
    if name_issues:
        print("⚠️ Windows 금지 이름/문자 패턴 감지 — 치환 규칙으로 생성 계속 진행합니다.\n")
        for p, why in name_issues:
            print(f" - {p}  ← {why}")

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
