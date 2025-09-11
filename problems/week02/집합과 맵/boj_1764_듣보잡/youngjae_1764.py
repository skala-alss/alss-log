# 듣보잡 (1764)
# https://www.acmicpc.net/problem/1764

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n, m = map(int, sys.stdin.readline().split())
    
    nohear = set()
    for _ in range(n):
        name = sys.stdin.readline().strip()
        nohear.add(name)
    # print(nohear)
    unknown = []
    cnt = 0
    for _ in range(m):
        name = sys.stdin.readline().strip()
        if name in nohear:
            cnt += 1
            unknown.append(name)
    print(cnt)
    print("\n".join(sorted(unknown)))

if __name__ == "__main__":
    main()

