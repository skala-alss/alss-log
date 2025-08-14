# 문자와 문자열 (27866)
# https://www.acmicpc.net/problem/27866

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    lines = (line.strip() for line in sys.stdin if line.strip() != "")
    
    for word_line, num_line in zip(lines, lines):
        word = list(word_line)
        print(word)
        n = int(num_line)
        print(word[n-1])

if __name__ == "__main__":
    main()

