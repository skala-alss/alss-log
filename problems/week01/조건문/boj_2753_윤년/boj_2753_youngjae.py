# 윤년 (2753)
# https://www.acmicpc.net/problem/2753

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    # y = int(sys.stdin.readline())

    # if (y % 4 == 0 and y % 100 != 0) or (y % 400 ==0):
    #     print(1)
    # else:
    #     print(0)

    # N = int(input()); M = int(input())

    N, M = map(int, sys.stdin.readline().split())

    def isleaf (y):
        return (y % 4 == 0 and y % 100 != 0) or (y % 400 == 0)

    for y in (N, M):
        if isleaf(y):
            print(1)
        else:
            print(0)

if __name__ == "__main__":
    main()

