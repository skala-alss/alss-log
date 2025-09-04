# 에디터 (1406)
# https://www.acmicpc.net/problem/1406

def main() -> None:

    import sys
    from collections import deque

    sys.stdin = open("input.txt", "r")

    while True:
        line = sys.stdin.readline()
        if not line:
            break
        
        line = line.strip()
        if not line:
            continue
        
        left = deque(line)
        right = deque()
        # print(left)
        n = int(sys.stdin.readline().strip())
        # print(n)
        for _ in range(n):
            cmd = sys.stdin.readline().split()
            # print(cmd)
            if cmd[0] == 'L':
                if left:
                    right.appendleft(left.pop())
            elif cmd[0] == 'D':
                if right:
                    left.append(right.popleft())
            elif cmd[0] == 'B':
                if left:
                    left.pop()
            elif cmd[0] == 'P':
                left.append(cmd[1])  
        # print(*(left + right))         
        print("".join(left) + "".join(right))      

if __name__ == "__main__":
    main()

