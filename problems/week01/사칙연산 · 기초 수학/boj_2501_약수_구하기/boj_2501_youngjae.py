# 약수 구하기 (2501)
# https://www.acmicpc.net/problem/2501

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    # print(sys.stdin)
    for line in sys.stdin:
        arr = []
        if line.strip() == "":  # 빈 줄이면 skip
            continue
        a, b = map(int, line.split())
        # print(a, b)
        for i in range(1, a+1, +1):
            if a%i == 0:
                arr.append(i)
        # print(len(arr))
        # print(arr)
        if len(arr) < b:
            print(0)
        else:
            print(arr[b-1])      



if __name__ == "__main__":
    main()

