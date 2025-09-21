# 단어 공부 (1157)
# https://www.acmicpc.net/problem/1157

def main() -> None:

    import sys
    from collections import Counter

    sys.stdin = open("input.txt", "r")
    
    while True:
        line = sys.stdin.readline()
        if not line:
            break 
        word = line.strip().upper()
        if not word:
            continue
        
        counter = Counter(word)
        max_cnt = max(counter.values())
        most_common = [ch for ch, cnt in counter.items() if cnt == max_cnt]
        
        if len(most_common) > 1:
            print("?")
        else:
            print(most_common[0])
        

if __name__ == "__main__":
    main()

