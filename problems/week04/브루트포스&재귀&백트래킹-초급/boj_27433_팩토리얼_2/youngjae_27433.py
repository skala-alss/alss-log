# 팩토리얼 2 (27433)
# https://www.acmicpc.net/problem/27433

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    def factorial(n):
        if n <= 1:
            ans = 1
        else:
            ans = factorial(n-1) * n
        
        return ans
    
    while True:
        n = int(sys.stdin.readline().strip())
        print(factorial(n))
        
        line = sys.stdin.readline()
        if not line:
            break
        
        line = line.strip()
        if not line:
            continue
    
    
if __name__ == "__main__":
    main()

