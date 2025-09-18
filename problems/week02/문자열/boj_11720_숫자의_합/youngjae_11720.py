# 숫자의 합 (11720)
# https://www.acmicpc.net/problem/11720

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    while True:
        line = sys.stdin.readline()
        if not line:
            break
        n = int(line.strip())
        nums = sys.stdin.readline().strip()
        print(sum(int(num) for num in nums))
        
        line = sys.stdin.readline().strip()
        if not line:
            continue
        



if __name__ == "__main__":
    main()

