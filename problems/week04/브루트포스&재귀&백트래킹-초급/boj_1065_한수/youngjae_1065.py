# 한수 (1065)
# https://www.acmicpc.net/problem/1065

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    while True:
        line = sys.stdin.readline()
        if not line:
            break
        line = line.strip()
        if not line:
            continue
        n = int(line)
        if n == 0:
            break

        if n < 100:
            print(n)
            continue

        count = 99
        for i in range(100, min(n, 999) + 1):
            digits = list(map(int, str(i)))
            if digits[0] - digits[1] == digits[1] - digits[2]:
                count += 1

        print(count)

if __name__ == "__main__":
    main()

