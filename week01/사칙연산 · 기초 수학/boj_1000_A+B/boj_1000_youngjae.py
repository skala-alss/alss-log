# A+B (1000)
# https://www.acmicpc.net/problem/1000

def main() -> None:

    import sys
    from fractions import Fraction
    import math

    sys.stdin = open("input.txt", "r")

    N, M = map(Fraction, sys.stdin.readline().split())

    print(f"A: {float (N)} B: {float (M)}")
    print(f"A + B = {N + M}")

if __name__ == "__main__":
    main()

