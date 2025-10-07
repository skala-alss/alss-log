// 10971 – 외판원 순회 2
// https://www.acmicpc.net/problem/10971
// solved.ac: https://solved.ac/search?query=10971
// 시간 제한: 2 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver II
// 태그: 백트래킹, 브루트포스 알고리즘, 외판원 순회 문제
// 푼 사람 수: 15,413
// 평균 시도: 2.87

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
  vector<vector<int>> W(N, vector<int>(N));
  for (vector<int> &row : W)
    for (int &col : row)
      cin >> col;

  vector<vector<int>> dp(N, vector<int>(1 << N, 1e9));
  dp[0][1 << 0] = 0;

  for (int visited = 0; visited < 1 << N; ++visited)
    for (int cur = 0; cur < N; ++cur)
      if (visited & 1 << cur && dp[cur][visited] < 1e9)
        for (int next = 0; next < N; ++next)
          if (!(visited & 1 << next) && W[cur][next])
            dp[next][visited | (1 << next)] = min(dp[next][visited | (1 << next)], dp[cur][visited] + W[cur][next]);

  int result = 1e9;
  for (int last = 0; last < N; ++last)
    if (W[last][0])
      result = min(result, dp[last][(1 << N) - 1] + W[last][0]);

  cout << result;

  return 0;
}
