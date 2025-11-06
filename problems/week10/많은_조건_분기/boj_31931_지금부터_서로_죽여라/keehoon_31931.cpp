// 31931 – 지금부터 서로 죽여라
// https://www.acmicpc.net/problem/31931
// solved.ac: https://solved.ac/search?query=31931
// 시간 제한: 1 초
// 메모리 제한: 1024 MB
// 티어: 🟡 Gold I
// 태그: 게임 이론, 많은 조건 분기
// 푼 사람 수: 65
// 평균 시도: 4.40

#include <iostream>
#if defined(_WIN32)
#include <io.h>
#include <cstdio>
#else
#include <unistd.h>
#include <cstdio>
#endif

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // 표준입력이 터미널이면 input.txt로 대체 (파이프 입력 시에는 그대로 cin)
#if defined(_WIN32)
  if (_isatty(_fileno(stdin)))
  {
    freopen("input.txt", "r", stdin);
  }
#else
  if (isatty(fileno(stdin)))
  {
    freopen("input.txt", "r", stdin);
  }
#endif

  int T;
  cin >> T;
  while (T--)
  {
    long long X, Y, A, B, C, D;
    cin >> X >> Y >> A >> B >> C >> D;

    string result;

    auto ceil_div = [](long long n, long long d) -> long long
    {
      return (n + d - 1) / d;
    };

    if (A >= Y)
      result = "NARUTO";

    else if (C >= X + B)
      result = "SASUKE";

    else if (A <= D && C <= B)
      result = "DRAW";

    else if (A > D && C < B)
      result = "NARUTO";

    else if (A > D && C == B)
      result = (ceil_div(Y, A) <= ceil_div(X, C)) ? "NARUTO" : "DRAW";

    else if (A < D && C > B)
      result = "SASUKE";

    else if (A == D && C > B)
      result = (ceil_div(Y, A) > ceil_div(X, C)) ? "SASUKE" : "DRAW";

    else if (A > D && C > B)
      result = (ceil_div(Y, A) <= ceil_div(X, C)) ? "NARUTO" : "SASUKE";

    cout << result << '\n';
  }

  return 0;
}
