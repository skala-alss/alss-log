# 단어순서 뒤집기 (12605)
# https://www.acmicpc.net/problem/12605

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    n = int(sys.stdin.readline().strip())
        
    for i in range(n):
        wdlist = sys.stdin.readline().strip().split()
        word = " ".join(reversed(wdlist))
        print(f"Case #{i+1}: {word}")

if __name__ == "__main__":
    main()

