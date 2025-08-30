// 27433 – 팩토리얼 2
// https://www.acmicpc.net/problem/27433
// solved.ac: https://solved.ac/search?query=27433
// 시간 제한: 1 초
// 메모리 제한: 1024 MB
// 티어: 🟫 Bronze V
// 태그: 사칙연산, 수학
// 푼 사람 수: 20,853
// 평균 시도: 2.10

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

  int N;
  cin >> N;

  auto factorial = [](auto self, int n) -> long long
  {
    if (n <= 1)
      return 1LL;
    return n * self(self, n - 1);
  };

  cout << factorial(factorial, N);

  return 0;
}
