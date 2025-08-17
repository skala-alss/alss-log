// 1740 – 거듭제곱
// https://www.acmicpc.net/problem/1740
// solved.ac: https://solved.ac/search?query=1740
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver III
// 태그: 비트마스킹, 수학
// 푼 사람 수: 1,870
// 평균 시도: 1.86

#include <iostream>
#if defined(_WIN32)
#include <io.h>
#include <cstdio>
#else
#include <unistd.h>
#include <cstdio>
#endif

using namespace std;

long long pow_3(int exp)
{
  long long base = 3;
  long long result = 1;
  while (exp > 0)
  {
    if (exp & 1)
      result *= base;
    base *= base;
    exp >>= 1;
  }
  return result;
}

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

  long long N;
  cin >> N;

  long long result = 0;
  int digit = 0;
  while (N)
  {
    if (N & (1ll << digit))
    {
      result += pow_3(digit);
      N ^= 1ll << digit;
    }
    ++digit;
  }

  cout << result;
  return 0;
}
