// 1780 – 종이의 개수
// https://www.acmicpc.net/problem/1780
// solved.ac: https://solved.ac/search?query=1780
// 시간 제한: 2 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver II
// 태그: 분할 정복, 재귀
// 푼 사람 수: 24,796
// 평균 시도: 1.65

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

  vector<vector<int>> paper(N, vector<int>(N));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      cin >> paper[i][j];

  vector<vector<vector<int>>> psums(3, vector<vector<int>>(N + 1, vector<int>(N + 1)));

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
    {
      int neq = paper[i - 1][j - 1] == -1 ? 1 : 0;
      int zero = paper[i - 1][j - 1] == 0 ? 1 : 0;
      int pos = paper[i - 1][j - 1] == 1 ? 1 : 0;

      psums[0][i][j] = psums[0][i - 1][j] + psums[0][i][j - 1] - psums[0][i - 1][j - 1] + neq;
      psums[1][i][j] = psums[1][i - 1][j] + psums[1][i][j - 1] - psums[1][i - 1][j - 1] + zero;
      psums[2][i][j] = psums[2][i - 1][j] + psums[2][i][j - 1] - psums[2][i - 1][j - 1] + pos;
    }

  vector<int> cnts(3);

  auto get = [&](const auto &psum, int r1, int c1, int r2, int c2) -> int
  {
    return psum[r2][c2] - psum[r1][c2] - psum[r2][c1] + psum[r1][c1];
  };

  auto dnq = [&](auto &&self, int row, int col, int sz) -> void
  {
    int number = paper[row][col] + 1;
    int area = sz * sz;
    if (get(psums[number], row, col, row + sz, col + sz) == area)
      ++cnts[number];
    else
      for (int i = row; i < row + sz; i += sz / 3)
        for (int j = col; j < col + sz; j += sz / 3)
          self(self, i, j, sz / 3);
  };

  dnq(dnq, 0, 0, N);

  for (int &cnt : cnts)
    cout << cnt << '\n';

  return 0;
}
