# A×B (10998)
# https://www.acmicpc.net/problem/10998

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    for line in sys.stdin:
        if line.strip() == "":
            continue
        a, b = map(int, line.split())
        print(a*b)


if __name__ == "__main__":
    main()

