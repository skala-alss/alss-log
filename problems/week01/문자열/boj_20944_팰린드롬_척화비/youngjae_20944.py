# 팰린드롬 척화비 (20944)
# https://www.acmicpc.net/problem/20944

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    for line in sys.stdin:
        if line.strip() == "":
            continue
        n = int(line.strip())
        print('a'*n)
        
if __name__ == "__main__":
    main()

