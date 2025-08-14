# 막대기 (17608)
# https://www.acmicpc.net/problem/17608

def main() -> None:

    import sys
    import time
    
    t0 = time.perf_counter()

    sys.stdin = open("input.txt", "r")
    
    data = sys.stdin.read().strip()

    # 빈 줄 기준으로 블록 나누기
    blocks = data.split("\n\n")
    # print(blocks)
    # blocks2 = data.split("\n")
    # print(blocks2)
    
    groups = []
    counts = []
    for block in blocks:
        # print(block)
        lines = block.strip().split("\n")
        # print(lines)
        counts.append(int(lines[0]))
        nums = list(map(int, lines[1:]))
        # print(nums)
        groups.append(nums)
    
    # print(counts)
    # print(groups)
    
    for i in range(len(groups)):
        cnt = 1
        biggest = groups[i][len(groups[i])-1]
        for j in reversed(range(len(groups[i])-1)):    
            # print(groups[i][j])
            if groups[i][j] > biggest:
                biggest = groups[i][j]    
                cnt += 1
        print(cnt)      
    t1 = time.perf_counter()  
    print(f"전체: {t1 - t0:.6f}s")

    # arr = [int (line.strip()) for line in sys.stdin if line.strip() != ""]
    
    # groups = []
    # current = []
    # for line in sys.stdin:
    #     line = line.strip()
    #     if line =="":
    #         if current:
    #             groups.append(current)
    #             current = []
    #     else:
    #         current.append(int(line))
    
    # if current:
    #     groups.append(current)

            
    #==== 2차원 배열 만들기, 첫 줄 갯수를 읽지 않고 그냥 배열로 만듦 ====
    # groups = [[]]
    # for line in sys.stdin:
    #     line = line.strip()
    #     if line == "":
    #         groups.append([])
    #     else:
    #         groups[-1].append(int(line))
    # if groups and not groups[-1]:
    #     groups.pop()
    #=================================================================
    
    # print(len(groups))
    # for i in range(len(groups)):
    #     print(len(groups[i]))
        
    
    # arr1 = []
    # arr2 = []
    # target = arr1
    
    # for line in sys.stdin:
    #     line = line.strip()
    #     if line == "":
    #         target = arr2
    #     else:
    #         target.append(int(line))
            
    # cnt1 = 1
    # cnt2 = 1
    # biggest1, biggest2 = arr1[len(arr1)-1], arr2[len(arr2)-1]
    # # print(biggest1, biggest2)    
    # for i in reversed(range(len(arr1)-1)):
    #     if arr1[i] > biggest1:
    #         biggest1 = arr1[i]
    #         cnt1 += 1
    # print(cnt1)
    
    # for i in reversed(range(len(arr2)-1)):
    #     if arr2[i] > biggest2:
    #         biggest2 = arr2[i]
    #         cnt2 += 1
    # print(cnt2)
        
        
        

if __name__ == "__main__":
    main()

