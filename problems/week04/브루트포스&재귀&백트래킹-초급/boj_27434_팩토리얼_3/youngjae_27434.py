# 팩토리얼 3 (27434)
# https://www.acmicpc.net/problem/27434
def factorial_range(l, r):
        if r < l:
            return 1
        if r == l:
            return l
        mid = (l+r) //2
        return factorial_range(l, mid) * factorial_range(mid + 1, r)

def main() -> None:

    import sys
    
    sys.setrecursionlimit(200000)
    sys.stdin = open("input.txt", "r")

    while True:
        n = int(sys.stdin.readline().strip())
        print(factorial_range(1, n))
        
        line = sys.stdin.readline()
        if not line:
            break
        
        line = line.strip()
        if not line:
            continue

if __name__ == "__main__":
    main()

