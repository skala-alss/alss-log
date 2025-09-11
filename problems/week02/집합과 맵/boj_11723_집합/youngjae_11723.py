# 집합 (11723)
# https://www.acmicpc.net/problem/11723

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    s = set()
    # output = []
    
    for _ in range(n):
        line = list(map(str, sys.stdin.readline().split()))
        # print(line)
        # print(line[0])
        if line[0] == 'add':
            s.add(int(line[1]))
        elif line[0] == 'remove':
            s.discard(int(line[1]))
        elif line[0] == 'check':
            print(1 if int(line[1]) in s else 0)
            # output.append(1 if int(line[1]) in s else 0)
        elif line[0] == 'toggle':
            if int(line[1]) in s:
                s.discard(int(line[1]))
            else:
                s.add(int(line[1]))
        elif line[0] == 'all':
            s = set(map(int, range(1, 21)))
            # print(s)
        elif line[0] == 'empty':
            s = set()
            # print(s)
    # print("\n".join(output))
    
    # for _ in range(n):
    #     line = list(map(str, sys.stdin.readline().split()))
    #     # print(line)
    #     # print(line[0])
    #     if line[0] == 'add':
    #         s.add(int(line[1]))
    #     elif line[0] == 'remove':
    #         s.discard(int(line[1]))
    #     elif line[0] == 'check':
    #         output.append('1' if int(line[1]) in s else '0')
    #     elif line[0] == 'toggle':
    #         if int(line[1]) in s:
    #             s.discard(int(line[1]))
    #         else:
    #             s.add(int(line[1]))
    #     elif line[0] == 'all':
    #         s = set(map(str, range(1, 21)))
    #         # print(s)
    #     elif line[0] == 'empty':
    #         s = set()
    #         # print(s)
    # print("\n".join(output))

if __name__ == "__main__":
    main()

