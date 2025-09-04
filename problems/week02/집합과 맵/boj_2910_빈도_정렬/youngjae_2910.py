# 빈도 정렬 (2910)
# https://www.acmicpc.net/problem/2910

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    while True:
        n, m = map(int, sys.stdin.readline().split())
        nums = list(map(int, sys.stdin.readline().strip().split()))
        freq = {}
        
        for x in nums:
            if x in freq:
                freq[x] += 1
            else:
                freq[x] = 1
        # print(nums)
        # print(freq)
        sorted_freq = sorted(freq.items(), key = lambda x: -x[1])
        
        result = []
        for num, cnt in sorted_freq:
            result.extend([num] * cnt)
            
        print(*result)
        
        line = sys.stdin.readline()
        if not line:
            break
        line = line.strip()
        if not line:
            continue

if __name__ == "__main__":
    main()

