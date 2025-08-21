# 스물셋 (23251)
# https://www.acmicpc.net/problem/23251

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    arr = [sys.stdin.readline().strip() for _ in range(n)]
    # print(n)
    # print(arr)
    for i in range(len(arr)):
        print(23*int(arr[i]))
    
    
if __name__ == "__main__":
    main()

