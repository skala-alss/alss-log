# 병영외 급식 (30204)
# https://www.acmicpc.net/problem/30204

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    while True:
        line = sys.stdin.readline()
        if not line:
            break
        
        line = line.strip()
        if not line:
            continue
        
        n, x = map(int, line.split())
        arr = list(map(int, sys.stdin.readline().split()))
        # print(n, x)
        # print(arr)
        if sum(arr) % x == 0:
            print("1")
        else:
            print("0")
        
if __name__ == "__main__":
    main()

