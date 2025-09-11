# 파일 정리 (20291)
# https://www.acmicpc.net/problem/20291

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    
    files = {}
    for _ in range(n):
        name, ext = sys.stdin.readline().strip().split('.')
        files[ext] = files.get(ext, 0) + 1
    
    # print(files)
    for ext in sorted(files.keys()):
        print(ext, files[ext])
        
    # for name, ext in files.items():
    #     groups.setdefault(ext, []).append(name)       
    # # print(files)
    
if __name__ == "__main__":
    main()

