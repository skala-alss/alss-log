# A+B - 4 (10951)
# https://www.acmicpc.net/problem/10951

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    for line in sys.stdin:
        a, b = map(int, line.split())
        print(a+b)

if __name__ == "__main__":
    main()

