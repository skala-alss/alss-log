# 큐 2 (18258)
# https://www.acmicpc.net/problem/18258

def main() -> None:

    import sys
    from collections import deque

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    stacks = deque()
    for line in sys.stdin:
        line = list(map(str, line.split()))
        # print(line)
        if line[0] == 'push':
            stacks.append(int(line[1]))
            
        elif line[0] == 'pop':
            if not stacks:
                print(-1)
            else:
                print(stacks.popleft())
                
        elif line[0] == 'size':
            print(len(stacks))
            
        elif line[0] == 'empty':
            if not stacks:
                print(1)
            else:
                print(0)
        
        elif line[0] == 'front':
            if not stacks:
                print(-1)
            else:
                print(stacks[0])
                
        elif line[0] == 'back':
            if not stacks:
                print(-1)
            else:
                print(stacks[-1])           

if __name__ == "__main__":
    main()

