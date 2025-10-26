// 30242 – 🧩 N-Queen (Easy)
// https://www.acmicpc.net/problem/30242
// solved.ac: https://solved.ac/search?query=30242
// 시간 제한: 0.5 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold III
// 태그: 백트래킹
// 푼 사람 수: 121
// 평균 시도: 2.60

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

  int N;
  cin >> N;
  vector<int> rows(N), cols(N, 0), diag1(N * 2, 0), diag2(N * 2, 0);
  for (int &row : rows)
    cin >> row;

  for (int row = 0; row < N; ++row)
    if (rows[row])
    {
      int col = rows[row] - 1;
      cols[col] = 1;
      diag1[row - col + N - 1] = 1;
      diag2[row + col] = 1;
    }

  vector<int> result(N, 0);
  bool found = false;
  auto backtracking = [&](auto &&self, int row) -> void
  {
    if (found)
      return;

    if (row == N)
    {
      result = rows;
      found = true;
      return;
    }

    if (rows[row])
      self(self, row + 1);

    if (!rows[row])
      for (int col = 0; col < N; ++col)
        if (!cols[col] && !diag1[row - col + N - 1] && !diag2[row + col])
        {
          rows[row] = col + 1;
          cols[col] = diag1[row - col + N - 1] = diag2[row + col] = 1;
          self(self, row + 1);
          rows[row] = 0;
          cols[col] = diag1[row - col + N - 1] = diag2[row + col] = 0;
        }
  };

  backtracking(backtracking, 0);

  if (!found)
    cout << -1;
  else
    for (int &col : result)
      cout << col << ' ';

  return 0;
}
