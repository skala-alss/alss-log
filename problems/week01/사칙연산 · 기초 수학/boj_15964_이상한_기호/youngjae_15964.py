# 이상한 기호 (15964)
# https://www.acmicpc.net/problem/15964

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    class wrd:
        def __init__(self, value):
            self.value = value
        
        def __matmul__(self, other):
            return (self.value + other.value) * (self.value - other.value)
        
    for line in sys.stdin:
        if line.strip() == "":
            continue
        N, M = map(int,line.split())
        a = wrd(N)
        b = wrd(M)
        print(a@b)

if __name__ == "__main__":
    main()

