# 세로읽기 (10798)
# https://www.acmicpc.net/problem/10798

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    blocks = [[]]
    for line in sys.stdin:
        line = line.strip()
        if line == "":
            blocks.append([])
        else:
            blocks[-1].append(line)
    
    if blocks and not blocks[-1]:
        blocks.pop()
    
    # print(blocks)
    
    # print(len(blocks))
    for j in range(len(blocks)):
        max_len = max(len(line) for line in blocks[j])
        # print(max_len)
        result = []
        for i in range(max_len):
            for line in blocks[j]:
                if i < len(line):
                    # print(line[i])
                    result.append(line[i])
        print("".join(result))

if __name__ == "__main__":
    main()

