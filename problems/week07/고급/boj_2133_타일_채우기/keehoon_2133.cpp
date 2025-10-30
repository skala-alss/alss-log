// 2133 – 타일 채우기
// https://www.acmicpc.net/problem/2133
// solved.ac: https://solved.ac/search?query=2133
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: 🟡 Gold IV
// 태그: 다이나믹 프로그래밍
// 푼 사람 수: 18,011
// 평균 시도: 2.70

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
  vector<int> dp(31);
  dp[0] = 1;

  for (int i = 0; i <= N; ++i)
  {
    if (i >= 2)
      dp[i] += dp[i - 2] * 3;
    for (int j = 3; j <= i; ++j)
      if (j % 2 == 0)
        dp[i] += dp[i - j] * 2;
  }

  cout << dp[N];

  return 0;
}
