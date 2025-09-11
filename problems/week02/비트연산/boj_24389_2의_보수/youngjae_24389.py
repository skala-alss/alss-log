# 2의 보수 (24389)
# https://www.acmicpc.net/problem/24389

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    n = int(sys.stdin.readline().strip())
    
    mask = (1 << 32)-1
    
    a = n & mask
    b = (-n) & mask
    diff = a ^ b
    print(bin(diff).count("1"))
    
if __name__ == "__main__":
    main()

