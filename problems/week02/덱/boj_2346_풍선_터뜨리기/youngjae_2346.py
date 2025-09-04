# 풍선 터뜨리기 (2346)
# https://www.acmicpc.net/problem/2346

def main() -> None:

    import sys
    from collections import deque

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    vals = list(map(int, sys.stdin.readline().split()))
    
    dq = deque((i+1, vals[i]) for i in range(n))   ## index와 값을 쌍으로 저장

    result = []
    
    while dq:
        idx, move = dq.popleft()
        result.append(idx)
        
        if dq:
            if move > 0:
                dq.rotate(-(move-1))
            else:
                dq.rotate(-move)
                
    print(*result)    
        

if __name__ == "__main__":
    main()

