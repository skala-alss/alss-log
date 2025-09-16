# N과 M (2) (15650)
# https://www.acmicpc.net/problem/15650

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
        result = []
        visited = [False] * (n + 1)
        path = []
        def backtracking(start: int) -> None:
            if len(path) == m:
                result.append(" ".join(map(str, path)))
                return
            for i in range(start, n + 1):
                if not visited[i]:
                    visited[i] = True
                    path.append(i)
                    backtracking(i + 1)
                    path.pop()
                    visited[i] = False
        backtracking(1)
        print("\n".join(result))   
        
    

if __name__ == "__main__":
    main()

