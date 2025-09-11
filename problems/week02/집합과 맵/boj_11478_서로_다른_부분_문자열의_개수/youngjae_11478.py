# 서로 다른 부분 문자열의 개수 (11478)
# https://www.acmicpc.net/problem/11478

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    char = sys.stdin.readline().strip()
    n = len(char)
    ans = set()     # set은 자동으로 중복값은 저장이 안된다.
    
    for i in range(n):
        for j in range(i+1, n+1):
            ans.add(char[i:j])
    
    print(len(ans))

if __name__ == "__main__":
    main()

