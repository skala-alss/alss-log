// 2908 – 상수
// https://www.acmicpc.net/problem/2908
// solved.ac: https://solved.ac/search?query=2908
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: 🟫 Bronze II
// 태그: 구현, 수학
// 푼 사람 수: 104,901
// 평균 시도: 1.46

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

  int A, B;
  cin >> A >> B;

  A = ((A % 10) * 100) + (A % 100 - A % 10) + (A / 100);
  B = ((B % 10) * 100) + (B % 100 - B % 10) + (B / 100);

  cout << (A > B ? A : B);
  return 0;
}
