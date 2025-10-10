// 11657 – 타임머신
// https://www.acmicpc.net/problem/11657
// solved.ac: https://solved.ac/search?query=11657
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: 🟡 Gold IV
// 태그: 그래프 이론, 벨만–포드, 최단 경로
// 푼 사람 수: 13,173
// 평균 시도: 3.74

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

  struct Node
  {
    int u, v, w;
    Node() : u(0), v(0), w(0) {};
    // Node(int u, int v, int w) : u(u), v(v), w(w) {}
  };

  int N, M;
  cin >> N >> M;

  vector<Node> edge_list(M);
  for (Node &edge : edge_list)
    cin >> edge.u >> edge.v >> edge.w;

  vector<long long> dist(N + 1, 1e9);
  dist[1] = 0;
  for (int _ = 0; _ < N - 1; ++_)
  {
    bool updated = false;
    for (Node &edge : edge_list)
      if (dist[edge.u] != 1e9 && dist[edge.u] + edge.w < dist[edge.v])
      {
        dist[edge.v] = dist[edge.u] + edge.w;
        updated = true;
      }
    if (!updated)
      break;
  }

  for (Node &edge : edge_list)
    if (dist[edge.u] != 1e9 && dist[edge.u] + edge.w < dist[edge.v])
    {
      cout << -1;
      return 0;
    }

  for (int i = 2; i < N + 1; ++i)
    cout << (dist[i] != 1e9 ? dist[i] : -1) << '\n';

  return 0;
}
