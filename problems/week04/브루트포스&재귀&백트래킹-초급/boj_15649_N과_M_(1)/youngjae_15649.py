# N과 M (1) (15649)
# https://www.acmicpc.net/problem/15649

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
        n, m = map(int, line.split())
        visited = [False] * (n + 1)
        result = []
        def backtrack(depth: int) -> None:
            if depth == m:
                print(" ".join(map(str, result)))
                return
            for i in range(1, n + 1):
                if not visited[i]:
                    visited[i] = True
                    result.append(i)
                    backtrack(depth + 1)
                    visited[i] = False
                    result.pop()
        backtrack(0)    

if __name__ == "__main__":
    main()

