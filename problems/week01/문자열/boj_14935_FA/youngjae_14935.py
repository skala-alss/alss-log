# FA (14935)
# https://www.acmicpc.net/problem/14935

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.readline().strip())
    
    def F(x):
        l = str(x)
        first_digit = int(l[0])
        return first_digit * len(l)
        
    seen = set()
    while n not in seen:
        seen.add(n)
        new_n = F(n)
        if new_n == n:
            print("FA")
            break
        n = new_n
    else:
        print("NFA")
        

    
    # st = []
    # while n != 0:
    #     st.append(n%10)
    #     n = n//10
    # # print(n)
    # print(st)
 
if __name__ == "__main__":
    main()

