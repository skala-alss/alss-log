# A+B - 5 (10952)
# https://www.acmicpc.net/problem/10952

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    for line in sys.stdin:
        a, b = map(int, line.split())
        if a == 0 and b == 0:
            continue
        print(a+b)

if __name__ == "__main__":
    main()

