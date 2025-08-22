# 팩토리얼 (10872)
# https://www.acmicpc.net/problem/10872

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    def fact(n):
        f = 1
        if n > 0:
            while n:
                f *=n
                n = n-1
            return f
        elif n == 0:
            return 1
    
    for line in sys.stdin:
        if line.strip() == "":
            continue
        a = int(line)
        print(fact(a))
        
        
            

if __name__ == "__main__":
    main()

