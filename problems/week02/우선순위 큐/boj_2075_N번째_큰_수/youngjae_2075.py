# N번째 큰 수 (2075)
# https://www.acmicpc.net/problem/2075

def main() -> None:

    import sys
    import heapq

    sys.stdin = open("input.txt", "r")
    n = int(sys.stdin.readline().strip())
    arr = []
    for _ in range(n):
        line = list(map(int, sys.stdin.readline().split()))
        for x in line:
            if len(arr) < n:
                heapq.heappush(arr, x)
            else:
                if x > arr[0]:
                    heapq.heapreplace(arr, x)
        # print(*line)
        # heap = heapq.heapify(unpack)
        # heapq.heappush(arr, heap)
        # heapq.heappush(arr, line)
            print(arr)
    print(arr[0])
        
    # flat = [x for row in arr for x in row]
    # print(sorted(flat)[-5])




if __name__ == "__main__":
    main()

