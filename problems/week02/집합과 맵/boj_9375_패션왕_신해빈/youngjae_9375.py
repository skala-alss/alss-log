# 패션왕 신해빈 (9375)
# https://www.acmicpc.net/problem/9375

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    m = int(sys.stdin.readline().strip())
    for _ in range(m):
        n = int(sys.stdin.readline().strip())
        clothes = {}
        for _ in range(n):
            name, category = sys.stdin.readline().strip().split()
            clothes[category] = clothes.get(category, 0) + 1
        
        result = 1
        for cnt in clothes.values():
            result *= (cnt+1)
        print(result - 1)

if __name__ == "__main__":
    main()

