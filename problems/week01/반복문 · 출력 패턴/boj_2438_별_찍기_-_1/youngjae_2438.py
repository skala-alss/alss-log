# 별 찍기 - 1 (2438)
# https://www.acmicpc.net/problem/2438

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.read().strip())
    for i in range(1, n+1):
        print("*" * i)

if __name__ == "__main__":
    main()

