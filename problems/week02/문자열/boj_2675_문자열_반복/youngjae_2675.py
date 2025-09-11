# 문자열 반복 (2675)
# https://www.acmicpc.net/problem/2675

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    n = int(sys.stdin.readline().strip())
    for _ in range(n):
        r, t = sys.stdin.readline().split()
        r = int(r)
        # print(r, type(r), t, type(t))
        result = ""
        for char in t:
            result += char * r
        print(result)

if __name__ == "__main__":
    main()

