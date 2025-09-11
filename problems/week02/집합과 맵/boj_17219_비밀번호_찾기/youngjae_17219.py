# 비밀번호 찾기 (17219)
# https://www.acmicpc.net/problem/17219

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n, m = map(int, sys.stdin.readline().split())
    
    info = {}
    for _ in range(n):
        site, pw = sys.stdin.readline().split()
        # print(line)
        info[site] = pw
    # print(info)
    # print(len(info))
    for _ in range(m):
        query = sys.stdin.readline().strip()
        # print(query)
        # print(type(query))
        print(info[query])
    
if __name__ == "__main__":
    main()

