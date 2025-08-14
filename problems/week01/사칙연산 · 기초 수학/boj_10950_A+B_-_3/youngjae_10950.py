# A+B - 3 (10950)
# https://www.acmicpc.net/problem/10950

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline())
    
    for _ in range(n):
        a, b = map(int, sys.stdin.readline().split())
        print(a+b)

if __name__ == "__main__":
    main()

