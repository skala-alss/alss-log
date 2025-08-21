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
        stack, ans = [], []
        for i in range
    
    
    # print(stack)
    
    print(blocks)


if __name__ == "__main__":
    main()

