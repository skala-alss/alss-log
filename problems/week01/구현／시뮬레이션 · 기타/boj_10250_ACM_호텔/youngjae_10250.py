# ACM 호텔 (10250)
# https://www.acmicpc.net/problem/10250

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    t = int(sys.stdin.readline().strip())
    # # print(t)
    for i in range(t):
        h, w, n = map(int, sys.stdin.readline().split())
        if n % h == 0:
            y = str(h)
            x = str(n//h).zfill(2)
        else:
            x = str((n//h)+1).zfill(2)
            y = str(n % h)
        print(y+x)
    
    # for i in range(1, 14):
    #     print(str(i).zfill(2)+str(12))
        
if __name__ == "__main__":
    main()

