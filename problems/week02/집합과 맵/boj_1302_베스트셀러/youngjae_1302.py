# 베스트셀러 (1302)
# https://www.acmicpc.net/problem/1302

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    while True:
        n = int(sys.stdin.readline().strip())
        books = {}
        
        for _ in range(n):
            title = sys.stdin.readline().strip()
            if title in books:
                books[title] += 1
            else:
                books[title] = 1
                
        max_count = max(books.values())
        candidates = [title for title, count in books.items() if count == max_count]
        print(min(candidates))
        
        line = sys.stdin.readline()
        if not line:
            break
        
        line = line.strip()
        if not line:
            continue
        

if __name__ == "__main__":
    main()

