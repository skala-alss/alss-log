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

  auto is_coast = [&](int r, int c) -> bool
  {
    for (int d = 0; d < 4; ++d)
    {
      int nr = r + DR[d];
      int nc = c + DC[d];
      if (0 <= nr && nr < N && 0 <= nc && nc < N)
        if (map[nr][nc] == 0)
          return true;
    }

    return false;
  };

  int id = 0;
  vector<vector<int>> label(N, vector<int>(N, 0));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (map[i][j] == 1 && label[i][j] == 0)
      {
        ++id;
        queue<pair<int, int>> q;
        q.emplace(i, j);
        label[i][j] = id;
        while (!q.empty())
        {
          auto [r, c] = q.front();
          q.pop();
          for (int d = 0; d < 4; ++d)
          {
            int nr = r + DR[d];
            int nc = c + DC[d];
            if (0 <= nr && nr < N && 0 <= nc && nc < N && map[nr][nc] == 1 && label[nr][nc] == 0)
            {
              label[nr][nc] = id;
              q.emplace(nr, nc);
            }
          }
        }
      }

  queue<pair<int, int>> q;
  vector<vector<int>> dist(N, vector<int>(N, -1));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (map[i][j] == 1)
      {
        dist[i][j] = 0;
        if (is_coast(i, j))
          q.emplace(i, j);
      }

  int result = 200;
  while (!q.empty())
  {
    auto [r, c] = q.front();
    q.pop();
    for (int d = 0; d < 4; ++d)
    {
      int nr = r + DR[d];
      int nc = c + DC[d];
      if (0 <= nr && nr < N && 0 <= nc && nc < N)
      {
        if (map[nr][nc] == 0)
        {
          map[nr][nc] = 1;
          label[nr][nc] = label[r][c];
          dist[nr][nc] = dist[r][c] + 1;
          q.emplace(nr, nc);
        }

        else if (label[nr][nc] != label[r][c])
          result = min(result, dist[r][c] + dist[nr][nc]);
      }
    }
  }

  cout << result;

  return 0;
}
