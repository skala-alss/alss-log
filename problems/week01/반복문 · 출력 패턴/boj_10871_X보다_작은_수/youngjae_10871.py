# X보다 작은 수 (10871)
# https://www.acmicpc.net/problem/10871

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n, x = map(int, sys.stdin.readline().split())
    arr = list(map(int, sys.stdin.readline().split()))
    
    for i in range(n):
        if arr[i] < x:
            print(arr[i], end=" ")
            
if __name__ == "__main__":
    main()

