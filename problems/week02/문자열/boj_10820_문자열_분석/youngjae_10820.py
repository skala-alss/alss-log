# 문자열 분석 (10820)
# https://www.acmicpc.net/problem/10820

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    while True:
        line = sys.stdin.readline()
        if not line:
            break
        line = line.strip("\n")
        
        lower = upper = digit = space = 0
        for ch in line:
            if ch.islower():
                lower += 1
            elif ch.isupper():
                upper += 1
            elif ch.isdigit():
                digit += 1
            elif ch.isspace():
                space += 1
        print(lower, upper, digit, space)
        
        if not line:
            continue
        
if __name__ == "__main__":
    main()
    
    

