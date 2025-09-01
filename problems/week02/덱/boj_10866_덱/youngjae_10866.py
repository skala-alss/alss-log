# 덱 (10866)
# https://www.acmicpc.net/problem/10866

"""
push_front X: 정수 X를 덱의 앞에 넣는다.
push_back X: 정수 X를 덱의 뒤에 넣는다.
pop_front: 덱의 가장 앞에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
pop_back: 덱의 가장 뒤에 있는 수를 빼고, 그 수를 출력한다. 만약, 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
size: 덱에 들어있는 정수의 개수를 출력한다.
empty: 덱이 비어있으면 1을, 아니면 0을 출력한다.
front: 덱의 가장 앞에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
back: 덱의 가장 뒤에 있는 정수를 출력한다. 만약 덱에 들어있는 정수가 없는 경우에는 -1을 출력한다.
"""

def main() -> None:

    import sys
    from collections import deque

    sys.stdin = open("input.txt", "r")
    lines = [line.strip() for line in sys.stdin]
    
    idx = 0
    blocks = []
    while idx < len(lines):
        if lines[idx] == "":
            idx += 1
            continue
        
        n = int(lines[idx])
        idx += 1
        block = lines[idx:idx+n]
        blocks.append(block)
        idx += n
        
    for i in range(len(blocks)):
        dq = deque()
        for j in range(len(blocks[i])):
            line = blocks[i][j].split()
            # print(line)
            if line[0] == 'push_front':
                dq.appendleft(line[1])
                
            elif line[0] == 'push_back':
                dq.append(line[1])
                
            elif line[0] == 'pop_front':
                if not dq:
                    print(-1)
                else:
                    print(dq.popleft())
            
            elif line[0] == 'pop_back':
                if not dq:
                    print(-1)
                else:
                    print(dq.pop())
                    
            elif line[0] == 'size':
                print(len(dq))
                
            elif line[0] == 'empty':
                if not dq:
                    print(1)
                else:
                    print(0)
                
            elif line[0] == 'front':
                if not dq:
                    print(-1)
                else:
                    print(dq[0])
                
            elif line[0] == 'back':
                if not dq:
                    print(-1)
                else:
                    print(dq[-1])
        print()
            
            
    ##==========================================
    ##============= 정답은 맞음 =================
    ##==========================================
    # n = int(sys.stdin.readline().strip())
    
    # dq = deque()
    # for line in sys.stdin:
    #     line = list(map(str, line.split()))
    #     # print(line)
    #     if line[0] == 'push_front':
    #         dq.appendleft(line[1])
            
    #     elif line[0] == 'push_back':
    #         dq.append(line[1])
            
    #     elif line[0] == 'pop_front':
    #         if not dq:
    #             print(-1)
    #         else:
    #             print(dq.popleft())
        
    #     elif line[0] == 'pop_back':
    #         if not dq:
    #             print(-1)
    #         else:
    #             print(dq.pop())
                
    #     elif line[0] == 'size':
    #         print(len(dq))
            
    #     elif line[0] == 'empty':
    #         if not dq:
    #             print(1)
    #         else:
    #             print(0)
            
    #     elif line[0] == 'front':
    #         if not dq:
    #             print(-1)
    #         else:
    #             print(dq[0])
            
    #     elif line[0] == 'back':
    #         if not dq:
    #             print(-1)
    #         else:
    #             print(dq[-1])

if __name__ == "__main__":
    main()

