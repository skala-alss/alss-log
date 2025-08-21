# 사분면 고르기 (14681)
# https://www.acmicpc.net/problem/14681

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    data = sys.stdin.read().strip().split("\n\n")
    # print(data)
    arr = [list(map(int, block.split())) for block in data]
    # print(arr)
    for i in range(len(arr)):
        if arr[i][0] > 0 and arr[i][1] > 0:
            print("1")
        elif arr[i][0] < 0 and arr[i][1] > 0:
            print("2")
        elif arr[i][0] < 0 and arr[i][1] < 0:
            print("3")
        elif arr[i][0] > 0 and arr[i][1] < 0:
            print("4")

if __name__ == "__main__":
    main()

