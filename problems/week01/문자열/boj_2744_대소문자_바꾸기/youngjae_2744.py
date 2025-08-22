# 대소문자 바꾸기 (2744)
# https://www.acmicpc.net/problem/2744

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    # string = list(sys.stdin.readline().strip())
    # print(string)

    word = sys.stdin.readline().strip()
    print(word)
    a = list(word)
    print(a)
    print(word.swapcase())
    for i in range(len(a)):
        if a[i].isupper():
            a[i] = a[i].lower()
        elif a[i].islower():
            a[i] = a[i].upper()
    print(a)
    print("".join(a))
    

if __name__ == "__main__":
    main()

