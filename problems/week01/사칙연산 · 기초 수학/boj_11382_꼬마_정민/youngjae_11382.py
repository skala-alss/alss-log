# 꼬마 정민 (11382)
# https://www.acmicpc.net/problem/11382

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    L, N, M = map(int, sys.stdin.readline().split())

    print(L+N+M)

if __name__ == "__main__":
    main()

