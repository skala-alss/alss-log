# FA (14935)
# https://www.acmicpc.net/problem/14935

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    
    st = []
    while n != 0:
        st.append(n%10)
        n = n//10
    # print(n)
    print(st)

if __name__ == "__main__":
    main()

