# 벌집 (2292)
# https://www.acmicpc.net/problem/2292

def main() -> None:

    import sys
    import math
    
    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline())
    
    layer = 1
    max_num = 1

    while n > max_num:
        max_num += 6 * layer
        layer += 1

    print(layer)
    
    # def hive (x):
    #     if n < 1:
    #         return None

    #     n_real = (3+math.sqrt(12*x-3))/6
        
    #     if n_real % 1 == 0:
    #         return n_real
    #     elif n_real % 1 != 0:
    #         return math.ceil(n_real)
        
    
    # print(int(hive(n)))
                
if __name__ == "__main__":
    main()

