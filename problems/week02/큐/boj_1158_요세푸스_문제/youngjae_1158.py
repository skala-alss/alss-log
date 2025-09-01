# 요세푸스 문제 (1158)
# https://www.acmicpc.net/problem/1158

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n, k = map(int, sys.stdin.readline().split())
    
    # print(n,k)
    arr = list(range(1, n+1))
    # print(arr)
    stack = []
    idx = 0
    while arr:
        l = len(arr)
        idx = (idx + k -1) % l
        stack.append(arr.pop(idx))
        # print(arr)
        # print(stack)
        
    print("<" + ", ".join(map(str, stack)) + ">")

if __name__ == "__main__":
    main()

