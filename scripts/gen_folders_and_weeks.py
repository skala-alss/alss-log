#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
README의 📁 링크 → 폴더/.gitkeep 생성
README의 마커 블록(<!--START:PROGRESS:...-->/<!--END:...-->) → 문제 번호 추출 → config/weeks.yaml 병합 갱신

사용 예:
  # 모든 주차 README 스캔 + 폴더/주차 YAML 생성/병합
  python scripts/gen_folders_and_weeks.py --scan-all --problems-root problems --weeks-yaml config/weeks.yaml -v

  # 특정 README만 처리
  python scripts/gen_folders_and_weeks.py --readme problems/week02/README.md --weeks-yaml config/weeks.yaml -v

옵션:
  --no-weeks-yaml   : 폴더/ .gitkeep만 생성하고 weeks.yaml은 건드리지 않음
  --dry-run         : 생성/쓰기 없이 동작만 시뮬레이트
  -v / -vv          : 상세 로그
"""

from __future__ import annotations
import argparse, re, sys, unicodedata
from pathlib import Path, PurePosixPath
from urllib.parse import unquote
import yaml

# ──────────────────────────────────────────────────────────────────────
# 공통 유틸 (기존 make_gitkeep 로직 유지)
# ──────────────────────────────────────────────────────────────────────
_FORBID_MAP = {"/":"／","\\":"＼","?":"？",":":"：","*":"＊","\"":"＂","<":"＜",">":"＞","|":"｜"}
_RESERVED_WIN = re.compile(r"^(CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])$", re.IGNORECASE)
_ZWS_RE = re.compile(r"[\u200B\u200C\u200D\uFEFF]")

MD_LINK_RE = re.compile(r"""
    \[([^\]]+)\]\s*\(
      \s*(?:<([^>]+)>\s*|((?:[^()\\]|\\.)+))\s*
    \)
""", re.VERBOSE)
HTML_LINK_RE = re.compile(r'<a\s+[^>]*href="([^"]+)"[^>]*>(.*?)</a>', re.IGNORECASE | re.DOTALL)

START_RE = re.compile(r'<!--\s*START\s*:\s*([A-Z0-9_:\-]+)\s*-->', re.IGNORECASE)
END_RE   = re.compile(r'<!--\s*END\s*:\s*([A-Z0-9_:\-]+)\s*-->',   re.IGNORECASE)
TAG_RE   = re.compile(r'<!--\s*TAG\s*:\s*([A-Za-z0-9_\-]+)\s*-->', re.IGNORECASE)

def _strip_invisibles(s: str) -> str:
    s = _ZWS_RE.sub("", (s or "").replace("\xa0"," "))
    try: s = unicodedata.normalize("NFC", s)
    except Exception: pass
    return s

def sanitize_component_keep_spaces(part: str) -> str:
    s = _strip_invisibles(part or "")
    s = "".join(ch for ch in s if ord(ch) >= 32)
    for k,v in _FORBID_MAP.items(): s = s.replace(k, v)
    s = s.rstrip(" .")
    s = re.sub(r"^\.+", "", s)
    stem = (s.split(".",1)[0]).upper()
    if _RESERVED_WIN.match(stem):
        s = "_" + s
    return s or "_"

def extract_folder_links(md: str) -> list[str]:
    links = []
    # Markdown [텍스트](URL)
    for text, url_angle, url_plain in MD_LINK_RE.findall(md):
        if "📁" in text:
            url = (url_angle or url_plain or "").strip()
            if url.startswith("<") and url.endswith(">"):
                url = url[1:-1].strip()
            links.append(url)
    # HTML <a href="URL">...</a>
    for url, inner in HTML_LINK_RE.findall(md):
        if "📁" in inner:
            links.append(url.strip())

    out = []
    for l in links:
        if "://" in l:        # 외부 URL 제외
            continue
        out.append(_strip_invisibles(unquote(l)).rstrip("/"))
    # 순서 유지 중복 제거
    seen=set(); uniq=[]
    for l in out:
        if l not in seen:
            seen.add(l); uniq.append(l)
    return uniq

def build_safe_path(base: Path, parts: tuple[str,...]) -> Path:
    p = base
    for part in parts:
        if not part or part == ".": continue
        if part == "..":
            p = p / part; continue
        p = p / sanitize_component_keep_spaces(part)
    return p

def to_abs_paths(readme_path: Path, rel_links: list[str]) -> list[Path]:
    base = readme_path.parent.resolve()
    out=[]
    for link in rel_links:
        posix = PurePosixPath(link)
        abs_p = build_safe_path(base, posix.parts).resolve()
        try: abs_p.relative_to(base)  # base 밖 탈출 방지
        except ValueError: continue
        out.append(abs_p)
    # 정렬 + 중복 제거
    return sorted(set(out))

def make_dirs_and_gitkeep(targets: list[Path], dry=False, verbose:int=0) -> tuple[int,int]:
    created_gitkeep = 0
    for d in targets:
        if verbose: print(" - mkdir:", d)
        if dry:    continue
        d.mkdir(parents=True, exist_ok=True)
        gk = d / ".gitkeep"
        if not gk.exists():
            gk.touch()
            created_gitkeep += 1
    return (len(targets), created_gitkeep)

# ──────────────────────────────────────────────────────────────────────
# weeks.yaml 추출/병합
# ──────────────────────────────────────────────────────────────────────
def _split_row(line: str) -> list[str]:
    if not line.strip().startswith("|"): return []
    return [c.strip() for c in line.strip().strip("|").split("|")]

def _is_sep_row(cells: list[str]) -> bool:
    return all(re.match(r"^:?-{3,}:?$", c) or c=="" for c in cells)

def _find_heading_above(lines: list[str], start_idx: int) -> str | None:
    for i in range(start_idx-1, -1, -1):
        ln = lines[i].strip()
        if re.match(r"^#{2,6}\s+", ln):   # ##, ###, ...
            return re.sub(r"^#{2,6}\s+","", ln).strip()
    return None

def parse_groups_from_readme(md: str) -> list[dict]:
    """
    README에서 각 PROGRESS 블록을 찾아
      { key, marker, title, problems[, tag] } 리스트로 반환
    """
    text  = md
    lines = md.splitlines()
    groups = []

    for m in START_RE.finditer(text):
        marker = m.group(1).strip()      # e.g. PROGRESS:STACK
        if not marker.upper().startswith("PROGRESS:"):
            continue
        key = marker.split(":",1)[1].strip()
        start_pos = m.end()

        e = END_RE.search(text, start_pos)
        if not e or e.group(1).strip() != marker:
            continue
        block = text[start_pos:e.start()]

        # 헤딩(타이틀) 추출
        start_line_index = text[:m.start()].count("\n")
        title = _find_heading_above(lines, start_line_index) or key

        # 태그 추출: 블록 직전 몇 줄 + 블록 내부에서 <!--TAG:...-->
        vicinity = "\n".join(lines[max(0, start_line_index-5):start_line_index]) + "\n" + block
        tag = None
        mt = TAG_RE.search(vicinity)
        if mt: tag = mt.group(1).strip()

        # 표에서 "번호" 열을 찾아 정수 모으기
        bl = block.strip("\n").splitlines()
        hdr_i=None
        for i, ln in enumerate(bl):
            if ln.strip().startswith("|"):
                hdr_i=i; break
        problems=[]
        if hdr_i is not None and hdr_i+1 < len(bl):
            header = _split_row(bl[hdr_i])
            number_col=None
            for idx, col in enumerate(header):
                low = col.strip().lower()
                if low in ("번호","no","id","problem","problem id"):
                    number_col = idx; break
            for j in range(hdr_i+2, len(bl)):
                cells = _split_row(bl[j])
                if not cells or _is_sep_row(cells): 
                    continue
                if number_col is None or number_col >= len(cells): 
                    continue
                try:
                    pid = int(re.sub(r"[^\d]","", cells[number_col]))
                    problems.append(pid)
                except Exception:
                    pass

        g = {"key": key, "marker": marker, "title": title, "problems": sorted(set(problems))}
        if tag: g["tag"] = tag
        groups.append(g)

    return groups

def detect_week_id_and_relpath(readme_path: Path, problems_root="problems") -> tuple[str|int, str]:
    parts = readme_path.as_posix().split("/")
    # 상대경로(리포 루트 기준) 계산
    if problems_root in parts:
        idx = parts.index(problems_root)
        rel_path = "/".join(parts[idx:])
    else:
        rel_path = readme_path.as_posix()
    # week id 탐지 (week02, week2 등)
    week_id = "?"
    for p in parts:
        m = re.match(r"week\s*(\d+)", p, re.IGNORECASE)
        if m:
            week_id = int(m.group(1))
            break
    return week_id, rel_path

def load_weeks(path: Path) -> dict:
    if not path.exists(): return {"weeks": []}
    with open(path, "r", encoding="utf-8") as f:
        data = yaml.safe_load(f) or {}
    data.setdefault("weeks", [])
    return data

def save_weeks(path: Path, data: dict, dry=False):
    if dry:
        print(yaml.safe_dump(data, sort_keys=False, allow_unicode=True))
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w", encoding="utf-8") as f:
        yaml.safe_dump(data, f, sort_keys=False, allow_unicode=True)

def upsert_weeks_item(data: dict, item: dict, verbose:int=0):
    """
    data = {"weeks":[...]}
    item = {"id": 2, "path": "...", "groups": [...]}
    - 같은 id의 week가 있으면 path 갱신
    - 그룹(key)별로 problems ∪ 병합, marker/title/tag 최신값 반영
    """
    weeks = data.setdefault("weeks", [])
    # week 찾기/생성
    tgt = None
    for w in weeks:
        if str(w.get("id")) == str(item["id"]):
            tgt = w; break
    if tgt is None:
        tgt = {"id": item["id"], "path": item["path"], "groups": []}
        weeks.append(tgt)
    else:
        tgt["path"] = item["path"] or tgt.get("path")

    # 그룹 병합
    for g in item.get("groups", []):
        exists = None
        for gg in tgt["groups"]:
            if gg.get("key") == g["key"]:
                exists = gg; break
        if exists is None:
            tgt["groups"].append(g)
            if verbose: print(f"  + add group {g['key']} ({len(g['problems'])} pids)")
        else:
            # problems: ∪ 후 정렬
            merged = sorted(set((exists.get("problems") or [])) | set(g.get("problems") or []))
            exists["problems"] = merged
            # 메타데이터 최신화
            for k in ("marker","title","tag"):
                if g.get(k): exists[k] = g[k]
            if verbose: print(f"  * merge group {g['key']} → {len(merged)} pids")

    # week 정렬(숫자 id 우선)
    weeks.sort(key=lambda w: int(w["id"]) if str(w.get("id","")).isdigit() else 9999)

# ──────────────────────────────────────────────────────────────────────
# CLI
# ──────────────────────────────────────────────────────────────────────
def parse_args():
    p = argparse.ArgumentParser(description="README → 폴더/.gitkeep + weeks.yaml 생성기 (make_gitkeep 슈퍼셋)")
    p.add_argument("--readme", type=Path, help="단일 README 경로")
    p.add_argument("--scan-all", action="store_true", help="<problems-root>/week*/README.md 전부 스캔")
    p.add_argument("--problems-root", default="problems", help="주차 디렉토리 루트 (기본: problems)")
    p.add_argument("--weeks-yaml", type=Path, default=Path("config/weeks.yaml"), help="주차 정의 YAML 경로")
    p.add_argument("--no-weeks-yaml", action="store_true", help="weeks.yaml 갱신 생략")
    p.add_argument("--dry-run", action="store_true", help="실제 생성/쓰기 없이 점검만")
    p.add_argument("--verbose", "-v", action="count", default=0)
    return p.parse_args()

# ──────────────────────────────────────────────────────────────────────
# main
# ──────────────────────────────────────────────────────────────────────
def main():
    args = parse_args()

    # 스캔 대상 README 목록 수집
    targets: list[Path] = []
    if args.scan_all:
        root = Path(".").resolve()
        targets = [p.resolve() for p in sorted(root.glob(f"{args.problems_root}/week*/README.md"))]
        if not targets:
            print(f"⚠️ {args.problems_root}/week*/README.md 를 찾지 못했습니다.", file=sys.stderr)
    elif args.readme:
        if not args.readme.exists():
            print(f"❌ README 없음: {args.readme}", file=sys.stderr); sys.exit(2)
        targets = [args.readme.resolve()]
    else:
        print("❌ --scan-all 또는 --readme 를 지정하세요.", file=sys.stderr); sys.exit(2)

    # weeks.yaml 로드 (병합 모드)
    weeks_data = None if args.no_weeks_yaml else load_weeks(args.weeks_yaml)

    # 각 README 처리
    for readme in targets:
        md = readme.read_text(encoding="utf-8", errors="ignore")

        # 1) 📁 링크 기반 폴더/.gitkeep
        links = extract_folder_links(md)
        abs_targets = to_abs_paths(readme, links)
        if args.verbose:
            print(f"[{readme}] 폴더 대상 {len(abs_targets)}개")
        n_dirs, n_gk = make_dirs_and_gitkeep(abs_targets, dry=args.dry_run, verbose=args.verbose)
        if args.verbose:
            print(f" └─ 폴더 생성/확인: {n_dirs}개, .gitkeep 신규: {n_gk}개")

        # 2) PROGRESS 블록 → weeks.yaml 병합
        if not args.no_weeks_yaml:
            groups = parse_groups_from_readme(md)
            week_id, rel_path = detect_week_id_and_relpath(readme, problems_root=args.problems_root)
            item = {"id": week_id, "path": rel_path, "groups": groups}
            if args.verbose:
                print(f" └─ weeks item: id={item['id']} path={item['path']} groups={len(groups)}")
                for g in groups:
                    print(f"    - {g['key']:8s} : {len(g['problems']):3d} pids  ({g.get('marker')})")
            upsert_weeks_item(weeks_data, item, verbose=args.verbose)

    # 3) weeks.yaml 저장
    if (weeks_data is not None) and (not args.no_weeks_yaml):
        if args.verbose:
            print(f"[write] {args.weeks_yaml}")
        if args.dry_run:
            print("----- weeks.yaml (dry-run preview) -----")
        save_weeks(args.weeks_yaml, weeks_data, dry=args.dry_run)

    print("✅ 완료")

if __name__ == "__main__":
    main()
