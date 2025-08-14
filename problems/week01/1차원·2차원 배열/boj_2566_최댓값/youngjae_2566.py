# 최댓값 (2566)
# https://www.acmicpc.net/problem/2566

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    arr = [list(map(int, line.split())) for line in sys.stdin if line.strip()]
    rows = len(arr)
    cols = len(arr[0]) if rows > 0 else 0
    
    max_val = arr[0][0]
    max_i, max_j = 0, 0
    for i in range(rows):
        for j in range(cols):
            if arr[i][j] > max_val:
                max_val = arr[i][j]
                max_i, max_j = i, j
                
    print(max_val)
    print(max_i+1, max_j+1)
    # print(arr)
    # print(rows)
    # print(cols)

if __name__ == "__main__":
    main()

