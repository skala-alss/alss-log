# 점수 계산 (2822)
# https://www.acmicpc.net/problem/2822

def main() -> None:

    import sys
    import heapq
    
    sys.stdin = open("input.txt", "r")

    scores = []
    for i in range(8):
        line = int(sys.stdin.readline().strip())
        if len(scores) < 5:
            heapq.heappush(scores, (line, i+1))
        else:
            if line > scores[0][0]:
                heapq.heapreplace(scores, (line, i+1))
    total = sum(x[0] for x in scores)
    print(total)
    index = [x[1] for x in scores]
    print(*sorted(index), end="\n\n")


##====================================================================
##==============vscode 실행 결과 index우선으로 틀림======================
##====================================================================
    # while True:
    #     scores = []
    #     for i in range(8):
    #         line = int(sys.stdin.readline().strip())
    #         if len(scores) < 5:
    #             heapq.heappush(scores, (i+1, line))
    #         else:
    #             if line > scores[0][1]:
    #                 heapq.heapreplace(scores, (i+1, line))
    #     total = sum(x[1] for x in scores)
    #     print(total)
    #     index = [x[0] for x in scores]
    #     print(*sorted(index), end="\n\n")
        
    #     line = sys.stdin.readline()
    #     if not line:
    #         break
        
    #     line = line.strip()
    #     if not line:
    #         continue

if __name__ == "__main__":
    main()

