# 종이의 개수 (1780)
# https://www.acmicpc.net/problem/1780

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    paper = [list(map(int, sys.stdin.readline().strip().split())) for _ in range(n)]
    count = [0, 0, 0]
    stack = [(0, 0, n)]
    while stack:
        x, y, n = stack.pop()
        color = paper[x][y]
        for i in range(x, x + n):
            for j in range(y, y + n):
                if paper[i][j] != color:
                    for dx in range(3):
                        for dy in range(3):
                            stack.append((x + dx * (n // 3), y + dy * (n // 3), n // 3))
                    break
            else:
                continue
            break
        else:
            count[color + 1] += 1
    print("\n".join(map(str, count)))
    
    
if __name__ == "__main__":
    main()

