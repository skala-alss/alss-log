# 행렬 덧셈 (2738)
# https://www.acmicpc.net/problem/2738

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    m, n = map(int, sys.stdin.readline().split())

    arrA = [list(map(int, sys.stdin.readline().split())) for _ in range(m)]
    arrB = [list(map(int, sys.stdin.readline().split())) for _ in range(m)]
    
    result = [[arrA[i][j] + arrB[i][j] for j in range(n)] for i in range(m)]
    for i in range(m):
        for j in range(n):
            print(result[i][j], end= ' ')
        print()
    # print(arrA)
    # print(arrB)

if __name__ == "__main__":
    main()

