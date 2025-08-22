# N 찍기 (2741)
# https://www.acmicpc.net/problem/2741

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    n = int(sys.stdin.read().strip())
    for i in range(n):
        print(i+1)
        
if __name__ == "__main__":
    main()

