# 칸토어 집합 (4779)
# https://www.acmicpc.net/problem/4779

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
        length = 3 ** n
        result = ["-"] * length
        def cantor(start: int, end: int) -> None:
            if end - start < 3:
                return
            third = (end - start) // 3
            for i in range(start + third, start + 2 * third):
                result[i] = " "
            cantor(start, start + third)
            cantor(start + 2 * third, end)
        cantor(0, length)
        print("".join(result))       

if __name__ == "__main__":
    main()

