#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
render_svg.py
Usage:
  python scripts/render_svg.py [in_json] [out_dir]

Defaults:
  in_json = data/dashboard.json
  out_dir = assets/

Generates:
  - weekly-heatmap.svg
  - leaderboard.svg
  - trend-multiples.svg
"""

import os, sys, json, math, html
from typing import List

SYSTEM_FONT_STACK = 'ui-sans-serif, system-ui, -apple-system, "Segoe UI", Roboto, "Noto Sans KR", "Apple SD Gothic Neo", "Malgun Gothic", sans-serif'

def load_json(path: str):
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f)

def ensure_dir(p: str):
    os.makedirs(p, exist_ok=True)

def pct_to_color(p: float) -> str:
    """
    Heatmap 색조는 그대로 유지(파랑 계열), 명도만 비율에 따라 보정.
    다크모드에서는 텍스트/스트로크 대비만 변수로 맞춥니다.
    """
    p = max(0.0, min(100.0, float(p)))
    L = 92 - (57 * (p / 100.0))
    return f"hsl(210, 85%, {L:.1f}%)"

def escape(s: str) -> str:
    return html.escape(str(s), quote=True)

# ---------- Common style helpers ----------
def common_light_dark_style() -> str:
    """
    공통 팔레트 변수: 라이트 기본, 다크에서 오버라이드.
    각 SVG의 구체 스타일에서 이 변수를 활용합니다.
    """
    return f"""
    <style>
      svg {{
        font-family: {SYSTEM_FONT_STACK};
        background: none; /* transparent */
        /* Light (default) */
        --fg-strong:   #0f172a;  /* slate-900 */
        --fg-muted:    #334155;  /* slate-700 */
        --fg-muted-2:  #475569;  /* slate-600 */
        --axis:        #64748b;  /* slate-500 */
        --stroke:      #e2e8f0;  /* slate-200 */
        --panel-fill:  #ffffff;
        --panel-stk:   #e2e8f0;
        --track:       #f1f5f9;  /* slate-100 */
        --bar:         #38bdf8;  /* sky-400 */
        --line:        #06b6d4;  /* cyan-500 */
        --dot:         #06b6d4;
        --badge-fill:  #f1f5f9;
        --badge-stk:   #e2e8f0;
        --avg-fill:    #0ea5e9;  /* sky-500 */
        --avg-stk:     #bae6fd;  /* sky-200 */
        --pct-color:   #0f172a;
      }}

      @media (prefers-color-scheme: dark) {{
        svg {{
          --fg-strong:   #e5e7eb; /* slate-200 */
          --fg-muted:    #cbd5e1; /* slate-300 */
          --fg-muted-2:  #94a3b8; /* slate-400 */
          --axis:        #94a3b8; /* slate-400 */
          --stroke:      #334155; /* slate-700 */
          --panel-fill:  #0b1220; /* 어두운 보드판 느낌 */
          --panel-stk:   #334155;
          --track:       #1f2937; /* slate-800 */
          --bar:         #38bdf8; /* 그대로 가도 대비 충분 */
          --line:        #22d3ee; /* cyan-400 조금 더 밝게 */
          --dot:         #22d3ee;
          --badge-fill:  #111827; /* slate-900 */
          --badge-stk:   #334155;
          --avg-fill:    #38bdf8; /* 평칸도 다크에서 더 선명하게 */
          --avg-stk:     #075985; /* sky-700 */
          --pct-color:   #e5e7eb;
        }}
      }}

      @keyframes pop {{ 0%{{opacity:0; transform:scale(0.96)}} 100%{{opacity:1; transform:scale(1)}} }}
      @keyframes grow {{ to {{ width: var(--w); }} }}
      @keyframes draw {{
        from {{ stroke-dasharray:1000; stroke-dashoffset:1000; }}
        to   {{ stroke-dasharray:1000; stroke-dashoffset:0; }}
      }}
    </style>
    """

# ---------- Weekly Heatmap ----------
def render_weekly_heatmap(payload: dict) -> str:
    members: List[str] = payload["members"]
    weeks: List[str]   = payload["weeks"]           # 배정 0 주차 제외
    num = payload["weekly"]["num"]                  # [week][member]
    den = payload["weekly"]["den"]                  # [week]
    pct = payload["weekly"]["pct"]                  # [week][member]

    # layout
    cell_w, cell_h = 96, 44
    left_gutter = 84
    right_avg_w = 90
    top_gutter = 56  # 제목 제거했지만 레이아웃 안정성 위해 유지
    col_gap, row_gap = 8, 8

    rows = len(weeks)
    cols = len(members)

    width  = left_gutter + cols*(cell_w+col_gap) + right_avg_w
    height = top_gutter + rows*(cell_h+row_gap)

    def delay(i, j):  # s
        return 0.03 * (i*cols + j)

    # header
    header_cells = []
    for j, m in enumerate(members):
        x = left_gutter + j*(cell_w+col_gap)
        header_cells.append(f'''
          <g transform="translate({x},{top_gutter-28})">
            <text class="colhdr" x="{cell_w/2}" y="0"
                  text-anchor="middle" dominant-baseline="middle">{escape(m)}</text>
          </g>
        ''')
    header_avg = f'''
      <g transform="translate({left_gutter + cols*(cell_w+col_gap)},{top_gutter-28})">
        <text class="colhdr" x="{right_avg_w/2}" y="0"
              text-anchor="middle" dominant-baseline="middle">합계(%)</text>
      </g>
    '''

    # body
    body_rows = []
    for i, wk in enumerate(weeks):
        row_y = top_gutter + i*(cell_h+row_gap)

        # week label
        row_group = [f'''
          <g class="rowlabel" transform="translate({left_gutter-12},{row_y + cell_h/2})">
            <text x="-6" y="0" text-anchor="end" dominant-baseline="middle">{escape(wk)}</text>
          </g>
        ''']

        # member cells
        row_sum = 0
        row_den = den[i] * max(1, cols)
        for j in range(cols):
            v_pct = pct[i][j]
            v_num = num[i][j]
            row_sum += v_num
            cx = left_gutter + j*(cell_w+col_gap)
            cell = f'''
              <g transform="translate({cx},{row_y})">
                <g class="cell-anim" style="animation-delay:{delay(i,j):.2f}s">
                  <title>W{escape(wk)} · {escape(members[j])} · {v_pct}% ({v_num}/{den[i]})</title>
                  <rect rx="10" ry="10" width="{cell_w}" height="{cell_h}" fill="{pct_to_color(v_pct)}" />
                  <text class="pct" x="{cell_w/2}" y="{cell_h/2}"
                        text-anchor="middle" dominant-baseline="middle">{int(round(v_pct))}%</text>
                </g>
              </g>
            '''
            row_group.append(cell)

        # row average (합계%)
        avg_pct = 0 if row_den == 0 else round(row_sum / row_den * 100)
        avg_x = left_gutter + cols*(cell_w+col_gap)
        row_group.append(f'''
          <g transform="translate({avg_x},{row_y})">
            <g class="cell-anim avg" style="animation-delay:{delay(i,cols):.2f}s">
              <title>W{escape(wk)} · 전체 평균 {avg_pct}% (Σ분자={row_sum} / Σ분모={row_den})</title>
              <rect rx="10" ry="10" width="{right_avg_w}" height="{cell_h}" />
              <text class="pct" x="{right_avg_w/2}" y="{cell_h/2}"
                    text-anchor="middle" dominant-baseline="middle">{avg_pct}%</text>
            </g>
          </g>
        ''')

        body_rows.append("\n".join(row_group))

    # style
    style = f"""
    {common_light_dark_style()}
    <style>
      .colhdr {{ font-size: 12px; fill: var(--fg-muted); }}
      .rowlabel text {{ font-size: 12px; fill: var(--fg-muted-2); }}
      .cell-anim {{
        animation: pop .45s ease both;
        transform-box: fill-box;
        transform-origin: 50% 50%;
      }}
      .cell-anim rect {{ stroke: var(--stroke); stroke-width: 1; }}
      .cell-anim.avg rect {{ fill: var(--avg-fill); opacity:.16; stroke: var(--avg-stk); }}
      .pct {{ fill: var(--pct-color); font-size: 14px; font-weight: 700; }}
    </style>
    """

    return f'''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" role="img">
      {style}
      {''.join(header_cells)}
      {header_avg}
      {''.join(body_rows)}
    </svg>'''

# ---------- Leaderboard ----------
def render_leaderboard(payload: dict) -> str:
    lb = payload["leaderboard"]  # already sorted desc by pct in builder
    n = len(lb)

    left_label_w = 180
    chart_w      = 460
    row_h        = 44
    gap          = 8
    pad_top      = 24  # 제목 제거로 상단 패딩 축소
    height       = pad_top + n*(row_h+gap)
    width        = left_label_w + chart_w + 32

    bars = []
    for i, row in enumerate(lb):
        y = pad_top + i*(row_h+gap)
        name = row["name"]
        pct  = int(row["pct"])
        done = row["done"]; total = row["total"]
        delay = 0.06 * i

        bars.append(f'''
          <g transform="translate(0,{y})">
            <text class="name" x="16" y="{row_h/2+6}">{escape(name)}</text>
            <g transform="translate({left_label_w},0)">
              <rect class="track" width="{chart_w}" height="{row_h}" rx="10" ry="10"/>
              <rect class="bar" style="--w:{pct}%; animation-delay:{delay:.2f}s" width="0" height="{row_h}" rx="10" ry="10">
                <title>{escape(name)} · {pct}% ({done}/{total})</title>
              </rect>
              <text class="pct" x="{chart_w-12}" y="{row_h/2+6}">{pct}%</text>
              <text class="nd" x="{12}" y="{row_h/2+6}">{done}/{total}</text>
            </g>
          </g>
        ''')

    style = f"""
    {common_light_dark_style()}
    <style>
      .name {{ font-size:14px; fill: var(--fg-muted); font-weight:600; }}
      .track {{ fill: var(--track); }}
      .bar {{ fill: var(--bar); animation: grow 0.9s cubic-bezier(.2,.7,.2,1) forwards; }}
      .pct  {{ font-size:12px; fill: var(--fg-strong); text-anchor:end; font-weight:700; }}
      .nd   {{ font-size:12px; fill: var(--fg-strong); }}
    </style>
    """
    return f'''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" role="img">
      {style}
      {''.join(bars)}
    </svg>'''

# ---------- Trend (small multiples) ----------
def render_trend_multiples(payload: dict) -> str:
    members = payload["members"]
    weeks   = payload["trend"]["weeks"]
    series  = payload["trend"]["series"]  # name -> [pct...]

    # card layout
    card_w, card_h = 260, 170
    cols = 3
    rows = math.ceil(len(members)/cols)
    gap  = 14
    pad_top = 12  # 제목 제거
    width  = cols*card_w + (cols-1)*gap + 16
    height = pad_top + rows*card_h + (rows-1)*gap

    # inner chart area
    inset = 24
    cw, ch = card_w-2*inset, card_h-2*inset

    def path_for(values: List[float]):
        n = len(values)
        if n == 0: 
            return "", (inset, inset+ch)
        pts = []
        for i, v in enumerate(values):
            x = inset + (cw*(i/(n-1 if n>1 else 1)))
            y = inset + ch * (1 - (max(0, min(100, v))/100.0))
            pts.append((x, y))
        d = []
        for k, (x,y) in enumerate(pts):
            d.append(("M" if k==0 else "L") + f"{x:.1f},{y:.1f}")
        return " ".join(d), pts[-1] if pts else (inset, inset+ch)

    cards = []
    for idx, name in enumerate(members):
        r, c = divmod(idx, cols)
        ox = c*(card_w+gap)
        oy = pad_top + r*(card_h+gap)
        vals = series.get(name, [0]*len(weeks))
        d, last_xy = path_for(vals)
        lx, ly = last_xy
        delay = 0.12 * idx

        last_pct = int(round(vals[-1])) if vals else 0

        grid = f'''
          <g class="grid">
            <line x1="{inset}" y1="{inset}" x2="{inset+cw}" y2="{inset}" />
            <line x1="{inset}" y1="{inset+ch}" x2="{inset+cw}" y2="{inset+ch}" />
          </g>
        '''

        # x ticks (weeks)
        xticks = []
        if weeks:
            step = cw/(max(1, len(weeks)-1))
            for i,wk in enumerate(weeks):
                tx = inset + step*i
                xticks.append(f'<text class="xt" x="{tx}" y="{inset+ch+18}" text-anchor="middle">{escape(wk)}</text>')

        cards.append(f'''
          <g class="card" transform="translate({ox},{oy})">
            <rect class="panel" x="0" y="0" width="{card_w}" height="{card_h}" rx="16" ry="16"/>
            <text class="name" x="{inset}" y="{inset-6}">{escape(name)}</text>
            {grid}
            <path class="line" d="{d}" pathLength="1000" style="animation-delay:{delay:.2f}s">
              <title>{escape(name)} · {len(weeks)}주 추세</title>
            </path>
            <circle class="dot" cx="{lx:.1f}" cy="{ly:.1f}" r="3"/>
            <g class="lastlabel" transform="translate({lx+6:.1f},{ly-10:.1f})">
              <rect x="-4" y="-12" width="40" height="20" rx="6" ry="6"/>
              <text x="16" y="2" text-anchor="middle">{last_pct}%</text>
            </g>
            {''.join(xticks)}
          </g>
        ''')

    style = f"""
    {common_light_dark_style()}
    <style>
      .panel {{ fill: var(--panel-fill); stroke: var(--panel-stk); }}
      .name  {{ font-size:13px; font-weight:700; fill: var(--fg-strong); }}
      .grid line {{ stroke: var(--stroke); stroke-width:1; }}
      .line {{ fill:none; stroke: var(--line); stroke-width:2.2; animation: draw 1.1s ease forwards; }}
      .dot {{ fill: var(--dot); }}
      .lastlabel rect {{ fill: var(--badge-fill); stroke: var(--badge-stk); }}
      .lastlabel text {{ font-size:12px; fill: var(--fg-strong); font-weight:700; }}
      .xt {{ font-size:10px; fill: var(--axis); }}
    </style>
    """
    return f'''<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" role="img">
      {style}
      {''.join(cards)}
    </svg>'''

def main():
    in_json = sys.argv[1] if len(sys.argv) >= 2 else "data/dashboard.json"
    out_dir = sys.argv[2] if len(sys.argv) >= 3 else "assets"

    ensure_dir(out_dir)

    if not os.path.exists(in_json):
        print(f"[error] JSON not found: {in_json}\n"
              f" - Run the build job to generate data/dashboard.json, or pass a path explicitly.", flush=True)
        sys.exit(2)

    payload = load_json(in_json)

    with open(os.path.join(out_dir, "weekly-heatmap.svg"), "w", encoding="utf-8") as f:
        f.write(render_weekly_heatmap(payload))

    with open(os.path.join(out_dir, "leaderboard.svg"), "w", encoding="utf-8") as f:
        f.write(render_leaderboard(payload))

    with open(os.path.join(out_dir, "trend-multiples.svg"), "w", encoding="utf-8") as f:
        f.write(render_trend_multiples(payload))

    print("SVGs written to:", out_dir)

if __name__ == "__main__":
    main()
