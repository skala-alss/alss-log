# 회전하는 큐 (1021)
# https://www.acmicpc.net/problem/1021

def main() -> None:

    import sys
    from collections import deque

    sys.stdin = open("input.txt", "r")

    while True:
        line = sys.stdin.readline()
        if not line:
            break
        
        line = line.strip()
        if not line:
            continue
        
        n, m = map(int, line.split())
        arr = list(map(int, sys.stdin.readline().split()))
        
        dq = deque(range(1, n+1))
        cnt = 0
        
        for x in arr:
            idx = dq.index(x)
            if idx <= len(dq)//2:
                cnt += idx
                dq.rotate(-idx)
            else:
                cnt += len(dq) - idx
                dq.rotate(len(dq) - idx)
            
            dq.popleft()
        print(cnt)               

if __name__ == "__main__":
    main()

