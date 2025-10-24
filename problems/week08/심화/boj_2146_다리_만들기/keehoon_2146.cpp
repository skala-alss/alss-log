// 2146 – 다리 만들기
// https://www.acmicpc.net/problem/2146
// solved.ac: https://solved.ac/search?query=2146
// 시간 제한: 2 초
// 메모리 제한: 192 MB
// 티어: 🟡 Gold III
// 태그: 그래프 이론, 그래프 탐색, 너비 우선 탐색
// 푼 사람 수: 12,949
// 평균 시도: 2.81

#include <iostream>
#include <list>
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

  constexpr int DR[4] = {1, 0, -1, 0};
  constexpr int DC[4] = {0, 1, 0, -1};

  int N;
  cin >> N;

  vector<vector<int>> map(N, vector<int>(N));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      cin >> map[i][j];

  vector<list<pair<int, int>>> islands;
  islands.reserve(9'999);
  vector<vector<bool>> visited(N, vector<bool>(N, false));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (map[i][j] == 1 && !visited[i][j])
      {
        islands.emplace_back();
        islands.back().emplace_back(i, j);
        visited[i][j] = true;
        queue<pair<int, int>> q;
        q.emplace(i, j);
        while (!q.empty())
        {
          auto [r, c] = q.front();
          q.pop();

          for (int k = 0; k < 4; ++k)
          {
            int nr = r + DR[k];
            int nc = c + DC[k];
            if (0 <= nr && nr < N && 0 <= nc && nc < N && map[nr][nc] == 1 && !visited[nr][nc])
            {
              visited[nr][nc] = true;
              q.emplace(nr, nc);
              islands.back().emplace_back(nr, nc);
            }
          }
        }
      }

  struct Node
  {
    int r, c, dist;
    Node() : r(0), c(0), dist(0) {}
    Node(int r, int c, int dist) : r(r), c(c), dist(dist) {}
  };

  int result = 200;
  for (int i = 0; i < (int)islands.size(); ++i)
  {
    queue<Node> q;
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    for (auto [r, c] : islands[i])
    {
      visited[r][c] = true;
      q.push(Node(r, c, 0));
    }

    bool updated = false;
    while (!q.empty())
    {
      Node cur = q.front();
      q.pop();

      for (int j = 0; j < 4; ++j)
      {
        int nr = cur.r + DR[j];
        int nc = cur.c + DC[j];

        if (0 <= nr && nr < N && 0 <= nc && nc < N && !visited[nr][nc])
        {
          if (map[nr][nc] == 1)
          {
            result = min(result, cur.dist);
            updated = true;
            break;
          }
          visited[nr][nc] = true;
          q.emplace(nr, nc, cur.dist + 1);
        }
      }

      if (updated)
        break;
    }
  }

  cout << result;

  return 0;
}
