// 2830 – 행성 X3
// https://www.acmicpc.net/problem/2830
// solved.ac: https://solved.ac/search?query=2830
// 시간 제한: 1 초
// 메모리 제한: 192 MB
// 티어: 🟡 Gold III
// 태그: 비트마스킹, 수학
// 푼 사람 수: 808
// 평균 시도: 3.14

#include <iostream>
#include <vector>
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
  vector<int> bits(20, 0);

  for (int i = 1; i <= N; ++i)
  {
    unsigned int residence;
    cin >> residence;

    for (int n = 0; n < 20; ++n)
      if (residence & (1u << n))
        ++bits[n];
  }

  long long result = 0;
  for (int n = 0; n < 20; ++n)
    result += 1LL * bits[n] * (N - bits[n]) * (1 << n);

  cout << result;

  return 0;
}
