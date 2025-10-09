// 4485 – 녹색 옷 입은 애가 젤다지?
// https://www.acmicpc.net/problem/4485
// solved.ac: https://solved.ac/search?query=4485
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: 🟡 Gold IV
// 태그: 격자 그래프, 그래프 이론, 그래프 탐색, 데이크스트라, 최단 경로
// 푼 사람 수: 14,259
// 평균 시도: 1.91

#include <array>
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

  struct Node
  {
    int cost;
    int r;
    int c;

    bool operator<(const Node &other) const
    {
      return cost > other.cost;
    }

    Node(int cost, int r, int c) : cost(cost), r(r), c(c) {}
  };

  constexpr array<int, 4> DR = {1, 0, -1, 0};
  constexpr array<int, 4> DC = {0, 1, 0, -1};

  int N;
  int pid = 0;

  while (cin >> N)
  {
    if (N == 0)
      break;

    ++pid;
    vector<vector<int>> cave(N, vector<int>(N));
    for (vector<int> &row : cave)
      for (int &col : row)
        cin >> col;

    vector<vector<int>> dist(N, vector<int>(N, 1e9));
    priority_queue<Node> pq;
    pq.emplace(cave[0][0], 0, 0);

    while (!pq.empty())
    {
      Node cur = pq.top();
      pq.pop();

      if (cur.cost < dist[cur.r][cur.c])
        dist[cur.r][cur.c] = cur.cost;
      else
        continue;

      if (cur.r == N - 1 && cur.c == N - 1)
        break;

      for (int d = 0; d < 4; ++d)
      {
        int nr = cur.r + DR[d];
        int nc = cur.c + DC[d];

        if (0 <= nr && nr < N && 0 <= nc && nc < N && cur.cost + cave[nr][nc] < dist[nr][nc])
          pq.emplace(cur.cost + cave[nr][nc], nr, nc);
      }
    }

    cout << "Problem " << pid << ": " << dist[N - 1][N - 1] << '\n';
  }

  return 0;
}
