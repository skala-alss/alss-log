# 덱 2 (28279)
# https://www.acmicpc.net/problem/28279

def main() -> None:

    import sys
    from collections import deque

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    
    dq = deque()
    for line in sys.stdin:
        line = list(map(int, line.split()))
        
        if line[0] == 1:
            dq.appendleft(line[1])
        
        elif line[0] == 2:
            dq.append(line[1])
            
        elif line[0] == 3:
            if not dq:
                print(-1)
            else:
                print(dq.popleft())
        
        elif line[0] == 4:
            if not dq:
                print(-1)
            else:
                print(dq.pop())
        
        elif line[0] == 5:
            print(len(dq))
            
        elif line[0] == 6:
            if not dq:
                print(1)
            else:
                print(0)
        
        elif line[0] == 7:
            if not dq:
                print(-1)
            else:
                print(dq[0])
                
        elif line[0] == 8:
            if not dq:
                print(-1)
            else:
                print(dq[-1])

if __name__ == "__main__":
    main()

