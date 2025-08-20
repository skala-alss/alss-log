# 비숍 투어 (23885)
# https://www.acmicpc.net/problem/23885

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    while True:
        line = sys.stdin.readline()
        if not line:
            break
        
        line = line.strip()
        if not line:
            continue
        n, m = map(int, line.split())
        sx, sy = map(int, sys.stdin.readline().split())
        s = sx + sy
        ex, ey = map(int, sys.stdin.readline().split())
        e = ex + ey
        if n==1 or m==1:
            if sx==ex and sy==ey:
                print("YES")
            else:
                print("NO")
        
        elif s % 2 == 0:
            if e % 2 == 0:
                print("YES")
            else:
                print("NO")
                
        elif s % 2 == 1:
            if e % 2 == 1:
                print("YES")
            else:
                print("NO")
        
        
        # print(size)
        # print(start)
        # print(end)

if __name__ == "__main__":
    main()

