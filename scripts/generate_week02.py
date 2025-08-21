import os
from pathlib import Path

# 유형별로 들어갈 문제 수
type_limits = {
    "스택": 5,
    "큐": 5,
    "우선순위 큐": 5,
    "덱": 5,
    "연결리스트": 5,
    "집합과 맵": 15,
    "비트연산": 6,
    "문자열": float('inf'),  # 나머지
}

# 전체 문제 목록 (문제번호, 제목)
all_problems = [
    (17608, "막대기"), (12605, "단어순서_뒤집기"), (10828, "스택"), (1874, "스택_수열"),
    (1918, "후위_표기식"), (2161, "카드1"), (26042, "식당_입구_대기_줄"), (18258, "큐_2"),
    (1158, "요세푸스_문제"), (1966, "프린터_큐"), (1927, "최소_힙"), (11279, "최대_힙"),
    (11286, "절댓값_힙"), (2075, "N번째_큰_수"), (7662, "이중_우선순위_큐"), (10866, "덱"),
    (28279, "덱_2"), (1021, "회전하는_큐"), (2346, "풍선_터뜨리기"), (5430, "AC"),
    (1406, "에디터"), (5397, "키로거"), (31423, "신촌_통폐합_계획"), (23309, "철도_공사"),
    (30885, "Φ²"), (11723, "집합"), (7785, "회사에_있는_사람"), (2822, "점수_계산"),
    (10815, "숫자_카드"), (17219, "비밀번호_찾기"), (1764, "듣보잡"),
    (1620, "나는야_포켓몬_마스터_이다솜"), (1302, "베스트셀러"), (9375, "패션왕_신해빈"),
    (2910, "빈도_정렬"), (11478, "서로_다른_부분_문자열의_개수"), (20291, "파일_정리"),
    (2108, "통계학"), (21939, "문제_추천_시스템_Version_1"), (21944, "문제_추천_시스템_Version_2"),
    (24389, "2의_보수"), (1094, "막대기"), (1740, "거듭제곱"), (15787, "기차가_어둠을_헤치고_은하수를"),
    (10728, "XOR삼형제_1"), (2830, "행성_X3"), (10809, "알파벳_찾기"), (2675, "문자열_반복"),
    (10820, "문자열_분석"), (11720, "숫자의_합"), (1157, "단어_공부"), (2941, "크로아티아_알파벳"),
    (5622, "다이얼"), (2908, "상수"), (1259, "팰린드롬수"), (1213, "팰린드롬_만들기"),
    (1919, "애너그램_만들기"), (1316, "그룹_단어_체커"), (1543, "문서_검색")
]

# 유형별로 문제 분배
problem_types = {}
type_iter = iter(type_limits.items())
current_type, limit = next(type_iter)
count = 0

for problem in all_problems:
    if current_type not in problem_types:
        problem_types[current_type] = []
    if count < limit:
        problem_types[current_type].append(problem)
        count += 1
    else:
        current_type, limit = next(type_iter)
        problem_types[current_type] = [problem]
        count = 1

# 폴더 생성
base_path = Path("week02")

for type_name, problems in problem_types.items():
    type_folder = base_path / type_name
    for pid, title in problems:
        problem_folder = type_folder / f"boj_{pid}_{title}"
        problem_folder.mkdir(parents=True, exist_ok=True)
        (problem_folder / ".gitkeep").touch()

print("✅ 폴더 및 .gitkeep 생성 완료.")
