# 프린터 큐 (1966)
# https://www.acmicpc.net/problem/1966

def main() -> None:

    import sys
    from collections import deque

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    for _ in range(n):
        j, k = map(int, sys.stdin.readline().split())
        ques = deque(map(int, sys.stdin.readline().split()))
        # print(j, k)
        # print(ques)
        # print(max(ques))
        # print(ques[0])
        cnt = 0
        
        while ques:
            cur = ques.popleft()
            if k == 0:
                if ques and cur < max(ques):
                    ques.append(cur)
                    k = len(ques) - 1
                else:
                    cnt += 1
                    print(cnt)
                    break
            else:
                if ques and cur < max(ques):
                    ques.append(cur)
                else:
                    cnt += 1
                k -= 1
            

if __name__ == "__main__":
    main()

