# 최소공배수 (1934)
# https://www.acmicpc.net/problem/1934

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    N = int(sys.stdin.readline())
    
    def gcd(a,b):
        while b:
            a, b = b, a%b
        return a
    
    for _ in range(N):
        a, b = map(int, sys.stdin.readline().split())
        lcm = a*b//gcd(a,b)
        print(lcm)1
        
        
    
    # def is_prime(n):
    #     if n<2:
    #         return False
    #     for i in range(2,i):
    #         if n%i ==0:
    #             return False
    #     return True
    
    # for _ in range(N):
    #     A, B = map(int, sys.stdin.readline().split())
    #     a = max(A,B)
    #     b = min(A,B)
        
    #     if a%b ==0:
    #         print(a)
    #     elif a%b !=0:
    #         if is_prime(a) and is_prime(b):
    #             print(a*b)     
         
    

if __name__ == "__main__":
    main()

