// 15550 – if 2
// https://www.acmicpc.net/problem/15550
// solved.ac: https://solved.ac/search?query=15550
// 시간 제한: 2 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold IV
// 태그: 애드 혹
// 푼 사람 수: 684
// 평균 시도: 1.84

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

  double a = 16777217;
  int b = 16777217;
  float c = 16777217;
  if (a == b && b == c && c != a)
  {
    cout << "true" << '\n';
  }
  else
  {
    cout << "false" << '\n';
  }
  return 0;
}
