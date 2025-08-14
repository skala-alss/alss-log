# 아스키 코드 (11654)
# https://www.acmicpc.net/problem/11654

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    for line in sys.stdin:
        if line.strip() == "":
            continue
        # a = str(line.strip())
        # print(a)
        # print(type(a))
        print(type(line.strip()))
        print(ord(line.strip()))     

if __name__ == "__main__":
    main()

