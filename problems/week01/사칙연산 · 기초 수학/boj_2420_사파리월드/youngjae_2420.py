# 사파리월드 (2420)
# https://www.acmicpc.net/problem/2420

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    a, b = map(int, sys.stdin.readline().split())
    # print(abs(a-b))
    
    m = a-b
    
    if m < 0:
        ans = (m)*(-1)
        print(ans)
    else:
        print(m)

if __name__ == "__main__":
    main()

