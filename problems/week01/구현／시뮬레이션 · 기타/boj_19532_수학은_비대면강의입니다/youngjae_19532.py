# 수학은 비대면강의입니다 (19532)
# https://www.acmicpc.net/problem/19532

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    for line in sys.stdin:
        if line.strip() == "":
            continue
        
        a, b, c, d, e, f = map(int, line.split())
        x = (c*e-b*f)//(a*e-b*d)
        y = (a*f-c*d)//(a*e-b*d)
        print(x, y)

if __name__ == "__main__":
    main()

