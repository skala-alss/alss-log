# 주사위 세개 (2480)
# https://www.acmicpc.net/problem/2480

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    for line in sys.stdin:
        if line.strip() == "":
            continue
        arr = sorted(list(map(int, line.strip().split())))      
        biggest = arr[0]
        same = arr[0]
        count = 1
        for i in range(len(arr)-1):
            if arr[i] == arr[i+1]:
                count += 1
                same = arr[i]
            elif biggest < arr[i+1]:
                biggest = arr[i+1]
            
        # print(same)
        if count == 3:
            print(10000 + same * 1000)
        elif count == 2:
            print(1000 + same * 100)
        elif count == 1:
            print(biggest * 100)
        # print(count)
        # print(biggest)
                
            
            
        # print(arr)

if __name__ == "__main__":
    main()

