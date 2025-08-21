# 스택 (10828)
# https://www.acmicpc.net/problem/10828

def main() -> None:

    import sys

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

    
    # if stack:
    #     print(1)
    # else:
    #     print(0)
    for i in range(len(blocks)):
        stack = []
        for j in range(len(blocks[i])):
            cmd = blocks[i][j].split()
            if cmd[0] == 'push':
                stack.append(cmd[1])
            
            elif cmd[0] == 'pop':
                if stack:
                    print(stack.pop(len(stack)-1))
                else:
                    print(-1)
            
            elif cmd[0] == 'size':
                print(len(stack))
            
            elif cmd[0] == 'empty':
                if not stack:
                    print(1)
                else:
                    print(0)
                    
            elif cmd[0] == 'top':
                if not stack:
                    print(-1)
                else:
                    print(stack[-1])      
            
        # print('')
    
    # for i, b in enumerate(blocks, 1):
    #     print(f"Block {i}:")
    #     for cmd in b:
    #         print("  ", cmd.split())

    
    
    # print(lines)
    # for i in range(len(lines)):
    #     print(lines[i].split())
            
    
if __name__ == "__main__":
    main()

