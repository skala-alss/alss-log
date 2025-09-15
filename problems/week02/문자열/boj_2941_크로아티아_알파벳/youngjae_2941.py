# 크로아티아 알파벳 (2941)
# https://www.acmicpc.net/problem/2941

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    while True:
        word = sys.stdin.readline()
        if not word:
            break
        word = word.strip()
        if not word:
            continue
        
        croatia_alphabets = [
            "c=",
            "c-",
            "dz=",
            "d-",
            "lj",
            "nj",
            "s=",
            "z=",
        ]
        for ca in croatia_alphabets:
            word = word.replace(ca, "*")
        print(len(word))
        
if __name__ == "__main__":
    main()

