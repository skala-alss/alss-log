// 15486 – 퇴사 2
// https://www.acmicpc.net/problem/15486
// solved.ac: https://solved.ac/search?query=15486
// 시간 제한: 2 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold V
// 태그: 다이나믹 프로그래밍
// 푼 사람 수: 10,995
// 평균 시도: 2.48

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
  vector<int> T(N + 1), P(N + 1);
  for (int i = 1; i <= N; ++i)
    cin >> T[i] >> P[i];

  vector<int> dp(N + 2, 0);
  int tmp = 0;

  for (int i = 1; i <= N; ++i)
  {
    if (i + T[i] <= N + 1)
      dp[i + T[i]] = max(dp[i + T[i]], tmp + P[i]);
    tmp = max(tmp, dp[i + 1]);
  }

  cout << tmp;

  return 0;
}
