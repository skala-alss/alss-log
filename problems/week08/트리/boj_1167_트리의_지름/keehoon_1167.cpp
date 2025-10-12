// 1167 – 트리의 지름
// https://www.acmicpc.net/problem/1167
// solved.ac: https://solved.ac/search?query=1167
// 시간 제한: 2 초
// 메모리 제한: 256 MB
// 티어: 🟡 Gold II
// 태그: 그래프 이론, 그래프 탐색, 깊이 우선 탐색, 트리, 트리의 지름
// 푼 사람 수: 18,722
// 평균 시도: 2.89

#include <algorithm>
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

  int V;
  cin >> V;

  vector<vector<pair<int, int>>> adjacency_list(V + 1);
  for (int i = 0; i < V; ++i)
  {
    int u;
    cin >> u;
    while (true)
    {
      int v, w;
      cin >> v;
      if (v == -1)
        break;
      cin >> w;
      adjacency_list[u].emplace_back(v, w);
      adjacency_list[v].emplace_back(u, w);
    }
  }

  vector<bool> visited(V + 1, false);
  vector<int> dist(V + 1, 0);
  auto dfs = [&](auto &&self, int cur) -> void
  {
    for (auto &[nxt, w] : adjacency_list[cur])
      if (!visited[nxt])
      {
        visited[nxt] = true;
        dist[nxt] = dist[cur] + w;
        self(self, nxt);
      }
  };

  visited[1] = true;
  dfs(dfs, 1);
  int border = max_element(dist.begin(), dist.end()) - dist.begin();

  fill(visited.begin(), visited.end(), false);
  fill(dist.begin(), dist.end(), 0);
  visited[border] = true;
  dfs(dfs, border);

  cout << *max_element(dist.begin(), dist.end());

  return 0;
}
