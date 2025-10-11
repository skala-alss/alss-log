// 1005 – ACM Craft
// https://www.acmicpc.net/problem/1005
// solved.ac: https://solved.ac/search?query=1005
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold III
// 태그: 그래프 이론, 다이나믹 프로그래밍, 방향 비순환 그래프, 위상 정렬
// 푼 사람 수: 18,830
// 평균 시도: 3.25

#include <iostream>
#include <vector>
#include <queue>
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

  int T;
  cin >> T;
  while (T--)
  {
    int N, K;
    cin >> N >> K;

    vector<vector<int>> adjacency_list(N + 1);
    vector<int> time(N + 1), in_degrees(N + 1, 0), dp(N + 1, 0);

    for (int i = 1; i <= N; ++i)
      cin >> time[i];

    while (K--)
    {
      int u, v;
      cin >> u >> v;
      adjacency_list[u].push_back(v);
      ++in_degrees[v];
    }

    queue<int> q;
    for (int i = 1; i <= N; ++i)
      if (in_degrees[i] == 0)
      {
        q.push(i);
        dp[i] = time[i];
      }

    while (!q.empty())
    {
      int cur = q.front();
      q.pop();

      for (int &nxt : adjacency_list[cur])
      {
        dp[nxt] = max(dp[nxt], time[nxt] + dp[cur]);
        if (--in_degrees[nxt] == 0)
          q.push(nxt);
      }
    }

    int W;
    cin >> W;
    cout << dp[W] << '\n';
  }

  return 0;
}
