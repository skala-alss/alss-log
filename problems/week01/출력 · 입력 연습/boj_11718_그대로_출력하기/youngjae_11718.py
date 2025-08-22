# 그대로 출력하기 (11718)
# https://www.acmicpc.net/problem/11718

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    for line in sys.stdin:
        if line.strip() == "":
            continue
        print(str(line.strip()))
    
if __name__ == "__main__":
    main()

