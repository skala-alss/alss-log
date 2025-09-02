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

  for (int mask = 0; mask < (1 << N); ++mask)
  {
    bool ok = true;
    for (auto &clause : clauses)
    {
      auto eval = [&](int x) -> bool
      {
        bool variable = mask & (1 << abs(x) - 1);
        return x > 0 ? variable : !variable;
      };

      if (!eval(clause.first) && !eval(clause.second))
      {
        ok = false;
        break;
      }
    }
    if (ok)
    {
      cout << 1 << '\n';
      return 0;
    }
  }
  cout << 0 << '\n';
  return 0;
}
