# 검증수 (2475)
# https://www.acmicpc.net/problem/2475

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    arr = list(map(int, sys.stdin.readline().split()))
    ans = 0
    for i in range(len(arr)):
        ans += arr[i]**2
    print(ans%10)

if __name__ == "__main__":
    main()  

