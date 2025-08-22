# 개수 세기 (10807)
# https://www.acmicpc.net/problem/10807

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    while True:
        n_line = sys.stdin.readline()
        if not n_line:  # EOF면 종료
            break       # "" 은 빈칸

        n_line = n_line.strip()
        # n_line = sys.stdin.readline().strip()  # break 안쓸때
        if not n_line:  # 빈 줄이면 이번 턴 스킵하고 다음 반복
            continue    # " " 은 빈 줄
        n = int(n_line)

        arr = list(map(int, sys.stdin.readline().split()))
        target = int(sys.stdin.readline())
        # target = int(n_line)  # break 안쓸때
        
        i = 0
        cnt = 0
        while i < n:
            if arr[i] == target:
                cnt += 1
            i += 1
        print(cnt)  # 직접 세기           

        count = arr.count(target)
        print(count)    # 함수 사용
        
        # print(f"원소개수: {n}")
        # print(f"배열: {arr}")
        # print(f"특정값: {target}")
        # print(f"개수: {count}")
        # print("---")
        
    # n = int(sys.stdin.readline())
    # arr = list(map(int, sys.stdin.readline().split()))
    # target = int(sys.stdin.readline())
    # i = 0
    # cnt = 0
    # while i<n:
    #     if arr[i] == target:
    #         cnt += 1
    #     i +=1

    # print(cnt)
    
if __name__ == "__main__":
    main()

