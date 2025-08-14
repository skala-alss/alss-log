# A/B (1008)
# https://www.acmicpc.net/problem/1008

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    for line in sys.stdin:
        if line.strip() == "":
            continue
        N, M = map(int, line.split())
        print(N/M)

if __name__ == "__main__":
    main()

