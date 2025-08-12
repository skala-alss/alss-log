# 윤년 (2753)
# https://www.acmicpc.net/problem/2753

def main() -> None:

    import sys

    # sys.stdin = open("input.txt", "r")

    # N, M = map(int, sys.stdin.readline().split())

    # print(f"N: {N} M: {M}")

    A = int(input("\n연도를 입력하세요 : "))
    B = int(input("하는 김에 하나 더 : "))


    # def leafyear(year: int) -> str:
    #     if (year % 4 == 0 and year % 100 != 0) or (year % 400 ==0):
    #         return "윤년"
    #     else:
    #         return "평년"

    def is_leaf(y):
        return (y % 4 == 0 and y % 100 != 0) or (y % 400 ==0)

    def leafyear(years: list[int]) -> str: 
        leaf_results = [is_leaf(y) for y in years]

        if all(leaf_results):
            return "둘다윤년"
        elif not any(leaf_results):
            return "둘다평년"
        else:
            return "윤년평년"
    
    years = [A, B]
    years.sort(key=lambda y: not is_leaf(y))


    # for year in years:
    if leafyear(years) == "둘다윤년":
        leaft = f"""예로부터 윤년이란 아주 귀찮은 개념이었지요.
일년에 지구가 태양을 한바퀴 도는 것을 선조들이 잘못 계산했기 때문이랍니다.
그것도 권력자들이 지들 멋대로 이래저래 바꿔대니 계산이 틀린 것이지요 빌어먹을.
때문에 이 귀찮은 것을 직접 계산한다면 다음과 같은 결과가 나오게 된답니다.
해당 연도를 4로 나눠서 떨어지면 윤녀이지만, 동시에 100으로 나눠서 떨어지면 평년이 되지요.
여기서 또 빌어먹을 것이 400으로 나눠서 떨어지면 또 다시 윤년이라 하더이다.
계산하는 후손의 입장에서는 참으로 거지같지요.
따라서 {years[0]}년은 윤년이라 할 수 있겠지요.
그리고 {years[1]}년도 윤년이 되겠습니다."""
        print(leaft)
    elif leafyear(years) == "둘다평년":
        nleaft = f"""예로부터 윤년이란 아주 귀찮은 개념이었지요.
일년에 지구가 태양을 한바퀴 도는 것을 선조들이 잘못 계산했기 때문이랍니다.
그것도 권력자들이 지들 멋대로 이래저래 바꿔대니 계산이 틀린 것이지요 빌어먹을.
때문에 이 귀찮은 것을 직접 계산한다면 다음과 같은 결과가 나오게 된답니다.
해당 연도를 4로 나눠서 떨어지면 윤녀이지만, 동시에 100으로 나눠서 떨어지면 평년이 되지요.
여기서 또 빌어먹을 것이 400으로 나눠서 떨어지면 또 다시 윤년이라 하더이다.
계산하는 후손의 입장에서는 참으로 거지같지요.
그래서 {years[0]}년이나 {years[1]}년 같은 연도는 밑도 끝도 없이 그냥 평년이랍니다.
왜냐구요? 직접 계산해 보세요 이 평년아. 아니 미안합니다.
한번 직접 계산해 보시는게 어떠실까요?"""
        print(nleaft)    
    elif leafyear(years) == "윤년평년":
        eachleaft = f"""예로부터 윤년이란 아주 귀찮은 개념이었지요.
일년에 지구가 태양을 한바퀴 도는 것을 선조들이 잘못 계산했기 때문이랍니다.
그것도 권력자들이 지들 멋대로 이래저래 바꿔대니 계산이 틀린 것이지요 빌어먹을.
때문에 이 귀찮은 것을 직접 계산한다면 다음과 같은 결과가 나오게 된답니다.
해당 연도를 4로 나눠서 떨어지면 윤녀이지만, 동시에 100으로 나눠서 떨어지면 평년이 되지요.
여기서 또 빌어먹을 것이 400으로 나눠서 떨어지면 또 다시 윤년이라 하더이다.
계산하는 후손의 입장에서는 참으로 거지같지요.
따라서 {years[0]}은 윤년이라 할 수 있겠지요.
그리고 {years[1]}은 평년이 되겠습니다."""
        print(eachleaft)

if __name__ == "__main__":
    main()

