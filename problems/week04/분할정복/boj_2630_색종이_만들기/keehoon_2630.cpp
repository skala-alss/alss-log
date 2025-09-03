// 2630 – 색종이 만들기
// https://www.acmicpc.net/problem/2630
// solved.ac: https://solved.ac/search?query=2630
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver II
// 태그: 분할 정복, 재귀
// 푼 사람 수: 33,592
// 평균 시도: 1.42

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
  for (vector<int> &line : paper)
    for (int &cell : line)
      cin >> cell;

  vector<vector<vector<int>>> psums(2, vector<vector<int>>(N + 1, vector<int>(N + 1)));
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
    {
      int zero = paper[i - 1][j - 1] == 0 ? 1 : 0;
      int one = paper[i - 1][j - 1] == 1 ? 1 : 0;

      psums[0][i][j] = psums[0][i - 1][j] + psums[0][i][j - 1] - psums[0][i - 1][j - 1] + zero;
      psums[1][i][j] = psums[1][i - 1][j] + psums[1][i][j - 1] - psums[1][i - 1][j - 1] + one;
    }

  vector<int> cnts(2, 0);

  auto get = [&](const auto &psum, int r1, int c1, int r2, int c2) -> int
  {
    return psum[r2][c2] - psum[r1][c2] - psum[r2][c1] + psum[r1][c1];
  };

  auto dnq = [&](auto &&self, int row, int col, int sz) -> void
  {
    int number = paper[row][col];
    int area = sz * sz;
    if (get(psums[number], row, col, row + sz, col + sz) == area)
      ++cnts[number];
    else
    {
      sz /= 2;
      self(self, row, col, sz);
      self(self, row + sz, col, sz);
      self(self, row, col + sz, sz);
      self(self, row + sz, col + sz, sz);
    }
  };

  dnq(dnq, 0, 0, N);

  cout << cnts[0] << '\n'
       << cnts[1];

  return 0;
}
