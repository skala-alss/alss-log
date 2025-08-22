// 1259 – 팰린드롬수
// https://www.acmicpc.net/problem/1259
// solved.ac: https://solved.ac/search?query=1259
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: 🟫 Bronze I
// 태그: 구현, 문자열
// 푼 사람 수: 43,830
// 평균 시도: 1.76

#include <algorithm>
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

  while (cin >> S)
  {
    if (S == "0")
      break;

    string OS = S;
    reverse(S.begin(), S.end());
    cout << (S == OS ? "yes" : "no") << '\n';
  }
  return 0;
}
