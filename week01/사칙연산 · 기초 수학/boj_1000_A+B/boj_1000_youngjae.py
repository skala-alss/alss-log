# A+B (1000)
# https://www.acmicpc.net/problem/1000

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    N, M = map(int, sys.stdin.readline().split())

    print(N+M)

if __name__ == "__main__":
    main()

