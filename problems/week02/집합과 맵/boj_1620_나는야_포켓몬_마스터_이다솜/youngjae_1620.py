# 나는야 포켓몬 마스터 이다솜 (1620)
# https://www.acmicpc.net/problem/1620

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n, m = map(int, sys.stdin.readline().split())
    
    pokedex_idx = {}
    pokedex_name = {}
    for i in range(n):
        pokemon = sys.stdin.readline().strip()
        pokedex_idx[i+1] = pokemon
        pokedex_name[pokemon] = i+1
    # print(pokedex_idx)
    # print(pokedex_name)
    for _ in range(m):
        query = sys.stdin.readline().strip()
        # print(type(query))
        if query.isdigit():
            # print(int(query))
            print(pokedex_idx[int(query)])
        else:
            print(pokedex_name[query])

if __name__ == "__main__":
    main()

