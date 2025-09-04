# 숫자 카드 (10815)
# https://www.acmicpc.net/problem/10815

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline())
    hand = set(map(int, sys.stdin.readline().split()))
    m = int(sys.stdin.readline())
    check = list(map(int, sys.stdin.readline().split()))
    
    for x in check:
        if x in hand:
            print(1, end=" ")
        else:
            print(0, end=" ")

if __name__ == "__main__":
    main()

