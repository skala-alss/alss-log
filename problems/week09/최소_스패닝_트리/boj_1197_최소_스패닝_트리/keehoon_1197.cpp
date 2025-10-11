// 1197 – 최소 스패닝 트리
// https://www.acmicpc.net/problem/1197
// solved.ac: https://solved.ac/search?query=1197
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: 🟡 Gold IV
// 태그: 그래프 이론, 최소 스패닝 트리
// 푼 사람 수: 24,872
// 평균 시도: 2.63

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

  struct Edge
  {
    int u, v, w;
    Edge() : u(0), v(0), w(0) {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}

    bool operator<(const Edge &other) const
    {
      return w < other.w;
    }
  };

  struct DSU
  {
    vector<int> parent, rank;

    DSU(int n)
    {
      parent.resize(n + 1);
      rank.resize(n + 1, 1);
      for (int i = 1; i <= n; ++i)
        parent[i] = i;
    }

    int find(int x)
    {
      if (parent[x] == x)
        return x;
      return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b)
    {
      a = find(a);
      b = find(b);
      if (a == b)
        return false;

      if (rank[a] < rank[b])
        swap(a, b);
      parent[b] = a;
      if (rank[a] == rank[b])
        ++rank[a];
      return true;
    }
  };

  int V, E;
  cin >> V >> E;
  vector<Edge> edges(E);
  for (Edge &edge : edges)
    cin >> edge.u >> edge.v >> edge.w;

  sort(edges.begin(), edges.end());

  DSU dsu(V);
  int result = 0, cnt = 0;
  for (Edge &edge : edges)
    if (dsu.unite(edge.u, edge.v))
    {
      result += edge.w;
      ++cnt;
      if (cnt == V - 1)
        break;
    }

  cout << result;

  return 0;
}
