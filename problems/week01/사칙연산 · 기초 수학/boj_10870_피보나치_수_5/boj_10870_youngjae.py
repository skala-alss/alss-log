# 피보나치 수 5 (10870)
# https://www.acmicpc.net/problem/10870

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    N = int(sys.stdin.readline())
    
    arr = []
    arr.extend([0,1])
    
    for i in range(len(arr), N+1):
        # print(arr[i-1])
        arr.append(arr[i-2] + arr[i-1])
        
    # print(arr)
    print(arr[N])
    
    

if __name__ == "__main__":
    main()

