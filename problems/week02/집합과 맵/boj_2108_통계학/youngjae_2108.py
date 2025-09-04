# 통계학 (2108)
# https://www.acmicpc.net/problem/2108

def main() -> None:

    import sys
    import math

    sys.stdin = open("input.txt", "r")
    
    n = int(sys.stdin.readline().strip())
    arr = []
    for _ in range(n):
        a = int(sys.stdin.readline().strip())
        arr.append(a)
        
    print(round(sum(arr)/n))
    
    sorted_arr = sorted(arr)
    print(sorted_arr[n//2])
    
    cnt = {}
    for x in arr:
        cnt[x] = cnt.get(x, 0) + 1            
    max_freq = max(cnt.values())
    modes = [k for k, v in cnt.items() if v == max_freq]
    modes.sort()
    
    if len(modes) > 1:
        print(modes[1])
    else:
        print(modes[0])
    
    print(max(sorted_arr) - min(sorted_arr))
    

    
    
    
    
    
    ##=============================================
    ##=============== 결과는 성공 ==================
    ##=============================================
    
    # while True:
    #     n = int(sys.stdin.readline().strip())
    #     arr = []
    #     for _ in range(n):
    #         a = int(sys.stdin.readline().strip())
    #         arr.append(a)
    #     # print(arr)
    #     print(round(sum(arr)/n))
        
    #     m = math.floor(n/2)
    #     sorted_arr = sorted(arr)
    #     print(sorted_arr[m])
        
    #     cnt = {}
    #     for x in arr:
    #         cnt[x] = cnt.get(x, 0) + 1            
    #     mode = max(cnt, key=cnt.get)
    #     print(mode)
        
    #     print(max(sorted_arr) - min(sorted_arr))
    #     print()
        
    #     line = sys.stdin.readline()
    #     if not line:
    #         break
    #     line = line.strip()
    #     if not line:
    #         continue

if __name__ == "__main__":
    main()

