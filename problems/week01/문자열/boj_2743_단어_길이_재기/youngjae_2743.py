# 단어 길이 재기 (2743)
# https://www.acmicpc.net/problem/2743

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    a = sys.stdin.readline().strip()
    print(list(a))
    print(len(list(a)))
    print(a)

if __name__ == "__main__":
    main()

