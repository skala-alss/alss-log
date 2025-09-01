# 스택 수열 (1874)
# https://www.acmicpc.net/problem/1874

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
        block = list(map(int, lines[idx:idx+n]))
        blocks.append(block)
        idx += n
        
        # print(block)
        stack, result = [], []
        current = 1
        for num in block:
            while current <= num:
                stack.append(current)
                result.append(f"+ push {current}, stack={stack}")
                current += 1
                
            if stack[-1] == num:
                stack.pop()
                result.append(f"- pop {num}, stack={stack}")
            else:
                print("NO")
                return
            
        for i in result:
            print(i)

    # print(stack)
    
    # print(blocks)

if __name__ == "__main__":
    main()


#========================== 제출본 =================================
# def main() -> None:

#     import sys
    
#     n = int(sys.stdin.readline().strip())
#     block = [int(sys.stdin.readline().strip()) for _ in range(n)]
    
#     stack, result = [], []
#     current = 1
#     for num in block:
#         while current <= num:
#             stack.append(current)
#             result.append('+')
#             current += 1
                
#         if stack[-1] == num:
#             stack.pop()
#             result.append('-')
#         else:
#             print("NO")
#             return
            
#     for i in result:
#         print(i)


# if __name__ == "__main__":
#     main()


