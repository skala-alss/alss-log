# 두 수 비교하기 (1330)
# https://www.acmicpc.net/problem/1330

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        a, b = map(int, line.split())
        if a < b:
            print("<")
        elif a > b:
            print(">")
        elif a == b:
            print("==")

if __name__ == "__main__":
    main()

