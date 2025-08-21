# 학점계산 (2754)
# https://www.acmicpc.net/problem/2754

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    
    grades = {
    "A+": 4.3, "A0": 4.0, "A-": 3.7,
    "B+": 3.3, "B0": 3.0, "B-": 2.7,
    "C+": 2.3, "C0": 2.0, "C-": 1.7,
    "D+": 1.3, "D0": 1.0, "D-": 0.7,
    "F": 0.0
    }
    
    grade = str(sys.stdin.readline().strip())
    print(grades[grade] if grade in grades else "error")

if __name__ == "__main__":
    main()

