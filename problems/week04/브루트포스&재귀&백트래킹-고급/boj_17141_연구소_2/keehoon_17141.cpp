// 17141 – 연구소 2
// https://www.acmicpc.net/problem/17141
// solved.ac: https://solved.ac/search?query=17141
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold IV
// 태그: 격자 그래프, 그래프 이론, 그래프 탐색, 너비 우선 탐색, 브루트포스 알고리즘
// 푼 사람 수: 4,336
// 평균 시도: 2.36

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

  constexpr int DR[4] = {-1, 0, 1, 0};
  constexpr int DC[4] = {0, 1, 0, -1};

  int N, M;
  cin >> N >> M;
  vector<int> lab(N * N);
  vector<int> pods;
  int blanks = 0;
  for (int i = 0; i < N * N; ++i)
  {
    cin >> lab[i];
    if (lab[i] == 2)
    {
      pods.push_back(i);
      lab[i] = 0;
    }
    if (lab[i] == 0)
      ++blanks;
  }

  int best = 1e9;
  deque<int> q;
  auto bfs = [&](vector<int> &graph) -> void
  {
    int last = 0;
    int spread = 0;
    while (!q.empty())
    {
      last = graph[q.front()];
      ++spread;
      int cr = q.front() / N;
      int cc = q.front() % N;
      q.pop_front();

      for (int i = 0; i < 4; ++i)
      {
        int nr = cr + DR[i];
        int nc = cc + DC[i];
        if (0 <= nr && nr < N && 0 <= nc && nc < N && graph[nr * N + nc] == 0)
        {
          graph[nr * N + nc] = graph[cr * N + cc] + 1;
          q.push_back(nr * N + nc);
        }
      }
    }

    best = blanks == spread ? min(best, last - 1) : best;
  };

  deque<int> dq;
  auto dfs = [&](auto &&self, int start) -> void
  {
    if (dq.size() == M)
    {
      vector<int> graph = lab;
      for (int &idx : dq)
        graph[idx] = 1;
      q = dq;
      bfs(graph);
      return;
    }

    for (int i = start; i < pods.size(); ++i)
    {
      dq.push_back(pods[i]);
      self(self, i + 1);
      dq.pop_back();
    }
  };

  dfs(dfs, 0);

  cout << (best != 1e9 ? best : -1);

  return 0;
}
