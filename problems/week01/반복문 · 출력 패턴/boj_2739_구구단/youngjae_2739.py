# 구구단 (2739)
# https://www.acmicpc.net/problem/2739

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    for i in range(1, 10):
        print(f"{n} * {i} = {n*i}")

if __name__ == "__main__":
    main()

