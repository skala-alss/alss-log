// 17619 – 개구리 점프
// https://www.acmicpc.net/problem/17619
// solved.ac: https://solved.ac/search?query=17619
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold III
// 태그: 분리 집합, 스위핑, 자료 구조, 정렬
// 푼 사람 수: 1,828
// 평균 시도: 3.53

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

  struct Node
  {
    int x1, x2, y, id;
    Node() : x1(0), x2(0), y(0), id(0) {}
    Node(int x1, int x2, int y, int id) : x1(x1), x2(x2), y(y), id(id) {}

    bool operator<(const Node &other) const
    {
      return x1 < other.x1;
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

    void unite(int a, int b)
    {
      a = find(a);
      b = find(b);
      if (a == b)
        return;

      if (rank[a] < rank[b])
        swap(a, b);
      parent[b] = a;
      if (rank[a] == rank[b])
        ++rank[a];
    }

    bool same(int a, int b)
    {
      return find(a) == find(b);
    }
  };

  int N, Q;
  cin >> N >> Q;

  vector<Node> logs;
  logs.reserve(N);
  for (int i = 1; i <= N; ++i)
  {
    int x1, x2, y;
    cin >> x1 >> x2 >> y;
    logs.emplace_back(x1, x2, y, i);
  }

  DSU dsu(N);

  sort(logs.begin(), logs.end());

  for (int i = 1; i < N; ++i)
    if (logs[i].x1 <= logs[i - 1].x2)
    {
      dsu.unite(logs[i].id, logs[i - 1].id);
      logs[i].x1 = min(logs[i].x1, logs[i - 1].x1);
      logs[i].x2 = max(logs[i].x2, logs[i - 1].x2);
    }

  while (Q--)
  {
    int a, b;
    cin >> a >> b;

    cout << (dsu.same(a, b) ? 1 : 0) << '\n';
  }

  return 0;
}
