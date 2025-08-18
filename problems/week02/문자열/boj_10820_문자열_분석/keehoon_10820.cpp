// 10820 – 문자열 분석
// https://www.acmicpc.net/problem/10820
// solved.ac: https://solved.ac/search?query=10820
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: 🟫 Bronze II
// 태그: 구현, 문자열
// 푼 사람 수: 12,883
// 평균 시도: 2.42

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

  string S;
  while (getline(cin, S))
  {
    int lower = 0, upper = 0, number = 0, space = 0;
    for (char l : S)
    {
      if (islower(l))
        ++lower;
      else if (isupper(l))
        ++upper;
      else if (isdigit(l))
        ++number;
      else if (isspace(l))
        ++space;
    }
    cout << lower << ' ' << upper << ' ' << number << ' ' << space << '\n';
  }
  return 0;
}
