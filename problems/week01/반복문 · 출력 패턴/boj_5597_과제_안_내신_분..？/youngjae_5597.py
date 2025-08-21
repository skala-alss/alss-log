# 과제 안 내신 분..? (5597)
# https://www.acmicpc.net/problem/5597

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    groups = [[]]   # 리스트 안에 리스트 준비
    for line in sys.stdin:
        line = line.strip()
        if line == "":   # 빈 줄이면 새 그룹 시작
            groups.append([])
        else:
            groups[-1].append(int(line))

    # 마지막에 빈 리스트가 있으면 제거
    if groups and not groups[-1]:
        groups.pop()
    for i in range(len(groups)):
        missing = set(range(1, 31)) - set(sorted(groups[i]))
        for x in sorted(missing):
            print(x)
    # # print(arr)
    # for i in range(1, 31):
    #     for j in range(len(arr)):
    #         if i != arr[j]:
               
if __name__ == "__main__":
    main()

