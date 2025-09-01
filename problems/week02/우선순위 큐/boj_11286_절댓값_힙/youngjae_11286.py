# 절댓값 힙 (11286)
# https://www.acmicpc.net/problem/11286

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
                print(heapq.heappop(arr)[1])
        else:
            heapq.heappush(arr, (abs(x), x))    # (절대값, 실제값) 형태의 튜플로 push
            
if __name__ == "__main__":
    main()

