# 회사에 있는 사람 (7785)
# https://www.acmicpc.net/problem/7785

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    # if 'as' == 'As':
    #     print(1)
    # else:
    #     print(0)
    n = int(sys.stdin.readline().strip())
    s = set()
    for _ in range(n):
        line = list(map(str, sys.stdin.readline().strip().split()))
        # print(line)
        if line[1] == 'enter':
            s.add(line[0])
        elif line[1] == 'leave':
            s.discard(line[0])
    
    # print(s)
    print("\n".join(map(str, sorted(s, reverse=True))))
        
    
if __name__ == "__main__":
    main()

