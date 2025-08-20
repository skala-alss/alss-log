# 블랙잭 (2798)
# https://www.acmicpc.net/problem/2798

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    while True:
        line = sys.stdin.readline()
        if not line:
            break
        
        line = line.strip()
        if not line:
            continue
        
        n, m = map(int, line.split())
        # print(n, m)
        
        cards = list(map(int, sys.stdin.readline().split()))
        sorted_cards = sorted(cards)
        
        blackJack = 0
        for i in range(n):
            for j in range(i+1, n):
                for k in range(j+1, n):
                    s = cards[i] + cards[j] + cards[k]
                    if s <= m:
                        blackJack = max(blackJack, s)
        print(blackJack)
        
        # print(cards)
        
        
if __name__ == "__main__":
    main()

