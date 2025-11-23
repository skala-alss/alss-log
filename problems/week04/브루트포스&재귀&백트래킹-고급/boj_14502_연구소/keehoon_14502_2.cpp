// 14502 – 연구소
// https://www.acmicpc.net/problem/14502
// solved.ac: https://solved.ac/search?query=14502
// 시간 제한: 2 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold IV
// 태그: 격자 그래프, 구현, 그래프 이론, 그래프 탐색, 너비 우선 탐색, 브루트포스 알고리즘
// 푼 사람 수: 40,522
// 평균 시도: 1.78

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
  int empties = 0;
  deque<pair<int, int>> viruses;
  vector<vector<int>> adjacency_matrix(N, vector<int>(M));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
    {
      cin >> adjacency_matrix[i][j];
      if (adjacency_matrix[i][j] == 0)
        ++empties;
      else if (adjacency_matrix[i][j] == 2)
        viruses.emplace_back(i, j);
    }

  int best = 0;

  auto bfs = [&](vector<vector<int>> graph) -> void
  {
    queue<pair<int, int>> q(viruses);

    int infested = 0;
    while (!q.empty())
    {
      auto [cr, cc] = q.front();
      q.pop();

      for (int d = 0; d < 4; ++d)
      {
        int nr = cr + DR[d];
        int nc = cc + DC[d];
        if (0 <= nr && nr < N && 0 <= nc && nc < M && graph[nr][nc] == 0)
        {
          graph[nr][nc] = 2;
          ++infested;
          q.emplace(nr, nc);
        }
      }
    }

    best = max(best, empties - infested - 3);
  };

  int idx = N * M;

  for (int i = 0; i < idx - 2; ++i)
  {
    int r1 = i / M;
    int c1 = i % M;
    if (adjacency_matrix[r1][c1] == 0)

      for (int j = i + 1; j < idx - 1; ++j)
      {
        int r2 = j / M;
        int c2 = j % M;
        if (adjacency_matrix[r2][c2] == 0)

          for (int k = j + 1; k < idx; ++k)
          {
            int r3 = k / M;
            int c3 = k % M;
            if (adjacency_matrix[r3][c3] == 0)

            {
              auto graph = adjacency_matrix;

              graph[r1][c1] = 1;
              graph[r2][c2] = 1;
              graph[r3][c3] = 1;

              bfs(graph);
            }
          }
      }
  }

  cout << best;

  return 0;
}
