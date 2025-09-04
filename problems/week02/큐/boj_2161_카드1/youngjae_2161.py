# 카드1 (2161)
# https://www.acmicpc.net/problem/2161

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    # print(n)
    cards = list(range(1, n+1))
    # print(cards)
    ans = []
    
    while cards:
        ans.append(cards.pop(0))
        # print(cards)
        if cards:
            cards.append(cards.pop(0))
        # print(ans)
        # print(cards)
        # print()
            
    print(*ans)

if __name__ == "__main__":
    main()

