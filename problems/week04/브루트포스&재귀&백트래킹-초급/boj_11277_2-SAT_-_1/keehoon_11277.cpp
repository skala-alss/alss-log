// 11277 – 2-SAT - 1
// https://www.acmicpc.net/problem/11277
// solved.ac: https://solved.ac/search?query=11277
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver I
// 태그: 브루트포스 알고리즘
// 푼 사람 수: 1,099
// 평균 시도: 1.61

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

  int N, M;
  cin >> N >> M;
  vector<pair<int, int>> clauses(M);
  for (auto &clause : clauses)
    cin >> clause.first >> clause.second;

  vector<bool> variables(N + 1);

  auto unsat_now = [&](int upto_idx) -> bool
  {
    for (const auto &clause : clauses)
    {
      int x = clause.first;
      int y = clause.second;
      int ax = abs(clause.first);
      int ay = abs(clause.second);
      bool x_assigned = ax <= upto_idx;
      bool y_assigned = ay <= upto_idx;
      if (x_assigned && y_assigned)
      {
        bool xv = variables[ax];
        bool yv = variables[ay];
        bool litx = (x > 0) ? xv : !xv;
        bool lity = (y > 0) ? yv : !yv;
        if (!litx && !lity)
          return true;
      }
    }
    return false;
  };

  auto dfs = [&](auto &&self, int idx) -> bool
  {
    if (unsat_now(idx - 1))
      return false;

    if (idx == N + 1)
    {
      for (auto &clause : clauses)
      {
        bool first = clause.first > 0 ? variables[clause.first] : !variables[-clause.first];
        bool second = clause.second > 0 ? variables[clause.second] : !variables[-clause.second];

        if (first == false && second == false)
          return false;
      }

      return true;
    }

    variables[idx] = true;
    if (self(self, idx + 1))
      return true;

    variables[idx] = false;
    if (self(self, idx + 1))
      return true;

    return false;
  };

  cout << (dfs(dfs, 1) ? 1 : 0);

  return 0;
}
