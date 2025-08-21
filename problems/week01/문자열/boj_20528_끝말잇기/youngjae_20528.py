# 끝말잇기 (20528)
# https://www.acmicpc.net/problem/20528

def main() -> None:

    import sys

    sys.stdin = open("input.txt", "r")
    lines = (line.strip() for line in sys.stdin if line.strip() != "")
    for num_line, str_line in zip(lines, lines):
        n = int(num_line)
        # print(n)
        word = str_line.split()
        # print(word)
        first = word[0][0]
        last = word[0][-1]
        possible = True
        for w in word:
            if not(w[0] == w[-1] == first  == last):
                possible = False
                break
        
        print(1 if possible else 0)
                
        # str1, str2, str3 = map(str, str_line.split())
        # print(str1, str2, str3)
    # ================================================================
    # # 시간복잡도 O(n)
    # def is_palindrome(s: str) -> bool:
    #     return s == s[::-1]   # 뒤집은 문자열과 같은지 비교, 직관적이다.
    
    # # 시간복잡도 O(1)
    # def is_pali_pointer(s: str) -> bool:
    #     i, j = 0, len(s)-1
    #     while i < j:
    #         if s[i] != s[j]:
    #             return False
    #         i += 1
    #         j -= 1
    #     return True

if __name__ == "__main__":
    main()

