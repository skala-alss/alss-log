# 막대기 (1094)
# https://www.acmicpc.net/problem/1094

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    while True:
        n = int(sys.stdin.readline().strip())
        
        print(bin(n).count("1"))            
        
        line = sys.stdin.readline()
        if not line:
            break
        line = line.strip()
        if not line:
            continue
        
if __name__ == "__main__":
    main()

