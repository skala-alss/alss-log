# 사칙연산 (10869)
# https://www.acmicpc.net/problem/10869

def main() -> None:

    import sys
    
    sys.stdin = open("input.txt", "r")

    a, b = map(int, sys.stdin.readline().split())

    print(a+b)
    print(a-b)
    print(a*b)
    print(a//b)
    print(a%b)

if __name__ == "__main__":
    main()

