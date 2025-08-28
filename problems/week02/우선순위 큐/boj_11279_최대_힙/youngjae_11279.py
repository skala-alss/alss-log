# 최대 힙 (11279)
# https://www.acmicpc.net/problem/11279

def main() -> None:

    import sys
    import heapq
    
    sys.stdin = open("input.txt", "r")
    n = int(sys.stdin.readline().strip())
    
    arr=[]
    for _ in range(n):
        x = int(sys.stdin.readline().strip())
        if x == 0:
            if not arr:
                print(0)
            else:
                print(-heapq.heappop(arr))
        else:
            heapq.heappush(arr, -x)
    
    # pos = list(range(1, 11))
    # neg = [-i for i in pos]
    # print(heapq.heappop(neg))
    # pos = [-i for i in neg]
    # print(pos)

if __name__ == "__main__":
    main()

