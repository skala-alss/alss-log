# 시험 성적 (9498)
# https://www.acmicpc.net/problem/9498

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")

    n = int(sys.stdin.read().strip())
    if 90 <= n <= 100:
        grade = "A"
    elif 80 <= n < 90:
        grade = "B"
    elif 70 <= n < 80:
        grade = "C"
    elif 60 <= n < 70:
        grade = "D"
    else:
        grade = "F"

    print(grade) 

if __name__ == "__main__":
    main()

