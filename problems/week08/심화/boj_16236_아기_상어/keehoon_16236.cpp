// 16236 – 아기 상어
// https://www.acmicpc.net/problem/16236
// solved.ac: https://solved.ac/search?query=16236
// 시간 제한: 2 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold III
// 태그: 구현, 그래프 이론, 그래프 탐색, 너비 우선 탐색, 시뮬레이션
// 푼 사람 수: 24,755
// 평균 시도: 2.22

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

  struct Fish
  {
    int dist, r, c;

    Fish() : dist(0), r(0), c(0) {}
    Fish(int dist, int r, int c) : dist(dist), r(r), c(c) {}

    bool operator<(const Fish &other) const
    {
      if (dist != other.dist)
        return dist < other.dist;
      if (r != other.r)
        return r < other.r;
      return c < other.c;
    };
  };

  constexpr int DR[4] = {1, 0, -1, 0};
  constexpr int DC[4] = {0, 1, 0, -1};

  const int INF = 1e9;

  int N;
  cin >> N;

  Fish closest;
  vector<vector<int>> space(N, vector<int>(N, 0));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
    {
      cin >> space[i][j];
      if (space[i][j] == 9)
      {
        closest.dist = INF;
        closest.r = i;
        closest.c = j;
      }
    }

  int size = 2;
  int cnt = 0;
  int result = 0;
  while (true)
  {
    int r = closest.r;
    int c = closest.c;

    queue<Fish> q;
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    q.push(Fish(0, r, c));
    visited[r][c] = true;
    bool updated = false;
    while (!q.empty())
    {
      Fish cur = q.front();
      q.pop();

      if (0 < space[cur.r][cur.c] && space[cur.r][cur.c] < size && cur.dist > 0)
      {
        closest = min(closest, cur);
        updated = true;
      }

      for (int i = 0; i < 4; ++i)
      {
        int nr = cur.r + DR[i];
        int nc = cur.c + DC[i];
        if (0 <= nr && nr < N && 0 <= nc && nc < N && space[nr][nc] <= size && !visited[nr][nc])
        {
          visited[nr][nc] = true;
          q.push(Fish(cur.dist + 1, nr, nc));
        }
      }
    }

    if (!updated)
    {
      cout << result;
      break;
    }

    if (++cnt == size)
    {
      ++size;
      cnt = 0;
    }
    space[r][c] = 0;
    space[closest.r][closest.c] = 9;
    result += closest.dist;
    closest.dist = INF;
  };

  return 0;
}
