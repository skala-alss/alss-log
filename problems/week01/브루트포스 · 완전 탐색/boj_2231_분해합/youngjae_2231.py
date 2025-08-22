# 분해합 (2231)
# https://www.acmicpc.net/problem/2231

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.read().strip())
    # n = 256
    start = max(1, n-9*len(str(n)))
    ans = 0
    
    for i in range(start,n):
        if i + sum(map(int, str(i))) == n:
            ans = i
            break

    print(ans)

if __name__ == "__main__":
    main()

