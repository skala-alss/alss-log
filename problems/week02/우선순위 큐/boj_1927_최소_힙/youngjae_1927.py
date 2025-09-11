# 최소 힙 (1927)
# https://www.acmicpc.net/problem/1927

def main() -> None:

    import sys
    import heapq
    
    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    arr = []
    
    for _ in range(n):
        x = int(sys.stdin.readline().strip())
        if x == 0:
            if not arr:
                print(0)
            else:
                print(heapq.heappop(arr))
        else:
            heapq.heappush(arr, x)

if __name__ == "__main__":
    main()

