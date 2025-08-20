# 일곱 난쟁이 (2309)
# https://www.acmicpc.net/problem/2309

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    arr = sorted([int(line.strip()) for line in sys.stdin if line.strip() != ""])
    # print(arr)
    # firstSeven = arr[:7]
    total = sum(arr)
    liar1, liar2 = 0, 0
    for i in range(9):
        for j in range(i+1, 9):
            if total -(arr[i] + arr[j]) == 100:
                liar1, liar2 = arr[i], arr[j]
                break
        if liar1 and liar2:
            break
        
    for i in range(len(arr)):
        if arr[i] != liar1 and arr[i] != liar2:
            print(arr[i])
    
        
if __name__ == "__main__":
    main()

