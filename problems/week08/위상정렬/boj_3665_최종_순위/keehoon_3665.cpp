// 3665 – 최종 순위
// https://www.acmicpc.net/problem/3665
// solved.ac: https://solved.ac/search?query=3665
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: 🟡 Gold I
// 태그: 그래프 이론, 방향 비순환 그래프, 위상 정렬
// 푼 사람 수: 4,970
// 평균 시도: 2.44

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

  int t;
  cin >> t;

  while (t--)
  {
    int n;
    cin >> n;
    vector<int> ranks(n);
    for (int i = 0; i < n; ++i)
      cin >> ranks[i];

    vector<vector<int>> adjacency_matrix(n + 1, vector<int>(n + 1, 0));
    vector<int> in_degrees(n + 1, 0);

    for (int i = 0; i < n; ++i)
      for (int j = i + 1; j < n; ++j)
      {
        int u = ranks[i], v = ranks[j];
        if (!adjacency_matrix[u][v])
        {
          adjacency_matrix[u][v] = 1;
          ++in_degrees[v];
        }
      }

    int m;
    cin >> m;
    while (m--)
    {
      int a, b;
      cin >> a >> b;

      if (adjacency_matrix[a][b])
      {
        adjacency_matrix[a][b] = 0;
        --in_degrees[b];
        adjacency_matrix[b][a] = 1;
        ++in_degrees[a];
      }
      else
      {
        adjacency_matrix[b][a] = 0;
        --in_degrees[a];
        adjacency_matrix[a][b] = 1;
        ++in_degrees[b];
      }
    }

    queue<int> q;
    for (int tid : ranks)
      if (in_degrees[tid] == 0)
        q.push(tid);

    string result;
    result.reserve(n);
    for (int step = 0; step < n; ++step)
    {
      bool ok = true;
      if (q.empty())
      {
        result = "IMPOSSIBLE";
        break;
      }

      if (q.size() > 1)
        ok = false;

      int u = q.front();
      q.pop();
      result += ok ? to_string(u) + ' ' : "? ";
      for (int v = 1; v <= n; ++v)
        if (adjacency_matrix[u][v])
          if (--in_degrees[v] == 0)
            q.push(v);
    }

    cout << result << '\n';
  }

  return 0;
}
