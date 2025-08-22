# 스택 수열 (1874)
# https://www.acmicpc.net/problem/1874

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    lines = [line.strip() for line in sys.stdin]
    
    idx = 0
    blocks = []
    while idx < len(lines):
        if lines[idx] == "":
            idx += 1
            continue
        
        n = int(lines[idx])
        idx += 1
        block = list(map(int, lines[idx:idx+n]))
        blocks.append(block)
        idx += n
        
        # print(block)
        stack, ans = [], []
        for i in range(n):
            
    
    
    # print(stack)
    
    print(blocks)


if __name__ == "__main__":
    main()


















def merge_sort(arr):
    if len(arr) < 2:
        return arr

    mid = len(arr) // 2
    low_arr = merge_sort(arr[:mid])
    high_arr = merge_sort(arr[mid:])

    merged_arr = []
    l = h = 0
    while l < len(low_arr) and h < len(high_arr):
        if low_arr[l] < high_arr[h]:
            merged_arr.append(low_arr[l])
            l += 1
        else:
            merged_arr.append(high_arr[h])
            h += 1
    merged_arr += low_arr[l:]
    merged_arr += high_arr[h:]
    return merged_arr