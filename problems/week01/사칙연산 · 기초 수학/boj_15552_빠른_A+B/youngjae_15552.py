# 빠른 A+B (15552)
# https://www.acmicpc.net/problem/15552

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    N = int(sys.stdin.readline())
    
    for _ in range(N):
        a, b = map(int, sys.stdin.readline().split())
        print(a+b)


if __name__ == "__main__":
    main()

