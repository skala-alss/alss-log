# 키로거 (5397)
# https://www.acmicpc.net/problem/5397

def main() -> None:

    import sys
    from collections import deque

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    for _ in range(n):
        src = list(sys.stdin.readline().strip())
        left = deque() 
        right = deque()
        for t in src:
            if t == '<':
                if left:
                    right.appendleft(left.pop())
            elif t == '>':
                if right:
                    left.append(right.popleft())
            elif t == '-':
                if left:
                    left.pop()
            else:
                left.append(t)
        print("".join(left) + "".join(right))  
                
if __name__ == "__main__":
    main()

# &lt;&lt;BP&lt;A&gt;&gt;Cd-