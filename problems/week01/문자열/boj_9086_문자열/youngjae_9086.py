# 문자열 (9086)
# https://www.acmicpc.net/problem/9086

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    for line in sys.stdin:
        string = list(line.strip())
        print(string[0], string[len(string)-1], sep='')    

if __name__ == "__main__":
    main()

