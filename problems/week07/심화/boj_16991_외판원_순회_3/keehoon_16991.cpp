// 16991 – 외판원 순회 3
// https://www.acmicpc.net/problem/16991
// solved.ac: https://solved.ac/search?query=16991
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold I
// 태그: 다이나믹 프로그래밍, 비트마스킹, 비트필드를 이용한 다이나믹 프로그래밍, 외판원 순회 문제
// 푼 사람 수: 1,019
// 평균 시도: 1.65

#include <cmath>
#include <iomanip>
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

  vector<pair<int, int>> cities(N);
  for (pair<int, int> &city : cities)
    cin >> city.first >> city.second;

  vector<vector<double>> dist(N, vector<double>(N, 0));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (i != j)
        dist[i][j] = hypot(cities[i].first - cities[j].first, cities[i].second - cities[j].second);

  vector<vector<double>> dp(N, vector<double>(1 << N, 8e6));

  dp[0][1] = 0;
  for (int visited = 0; visited < 1 << N; ++visited)
    for (int cur = 0; cur < N; ++cur)
      if (visited & 1 << cur)
        for (int next = 0; next < N; ++next)
          if (cur != next && !(visited & 1 << next))
            dp[next][visited | 1 << next] = min(dp[next][visited | 1 << next], dp[cur][visited] + dist[cur][next]);

  double result = 8e6;
  for (int i = 0; i < N; ++i)
    result = min(result, dp[i][(1 << N) - 1] + dist[i][0]);

  cout << fixed << setprecision(6) << result;

  return 0;
}
