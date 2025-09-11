# 알파벳 찾기 (10809)
# https://www.acmicpc.net/problem/10809

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    word = sys.stdin.readline().strip()
    for c in range(ord('a'), ord('z') + 1):
        print(word.find(chr(c)), end=" ")
    
if __name__ == "__main__":
    main()

