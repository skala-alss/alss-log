// 2056 – 작업
// https://www.acmicpc.net/problem/2056
// solved.ac: https://solved.ac/search?query=2056
// 시간 제한: 2 초
// 메모리 제한: 256 MB
// 티어: 🟡 Gold IV
// 태그: 그래프 이론, 다이나믹 프로그래밍, 방향 비순환 그래프, 위상 정렬
// 푼 사람 수: 6,744
// 평균 시도: 2.22

#include <algorithm>
#include <iostream>
#include <queue>
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
  vector<vector<int>> adjacency_list(N + 1);
  vector<int> time(N + 1), indegree(N + 1, 0), dp(N + 1, 0);

  for (int i = 1; i <= N; ++i)
  {
    int k;
    cin >> time[i] >> k;
    for (int j = 0; j < k; ++j)
    {
      int pre;
      cin >> pre;
      adjacency_list[pre].push_back(i);
      ++indegree[i];
    }
    dp[i] = time[i];
  }

  queue<int> q;
  for (int i = 1; i <= N; ++i)
    if (indegree[i] == 0)
      q.push(i);

  while (!q.empty())
  {
    int u = q.front();
    q.pop();
    for (int &v : adjacency_list[u])
    {
      dp[v] = max(dp[v], dp[u] + time[v]);
      if (--indegree[v] == 0)
        q.push(v);
    }
  }

  cout << *max_element(dp.begin(), dp.end());

  return 0;
}
