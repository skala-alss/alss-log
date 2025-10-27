// 14503 – 로봇 청소기
// https://www.acmicpc.net/problem/14503
// solved.ac: https://solved.ac/search?query=14503
// 시간 제한: 2 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold V
// 태그: 구현, 시뮬레이션
// 푼 사람 수: 30,067
// 평균 시도: 1.84

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

  constexpr int DR[4] = {-1, 0, 1, 0};
  constexpr int DC[4] = {0, 1, 0, -1};

  int N, M;
  cin >> N >> M;

  int cr, cc, dir;
  cin >> cr >> cc >> dir;

  vector<vector<int>> room(N, vector<int>(M));
  for (vector<int> &row : room)
    for (int &col : row)
      cin >> col;

  int result = 0;
  while (true)
  {
    if (room[cr][cc] == 0)
    {
      room[cr][cc] = 2;
      ++result;
      continue;
    }

    bool found = false;
    int nr, nc;
    for (int d = 1; d <= 4; ++d)
    {
      nr = cr + DR[(dir - d + 4) % 4];
      nc = cc + DC[(dir - d + 4) % 4];
      if (room[nr][nc] == 0)
      {
        cr = nr;
        cc = nc;
        dir = (dir - d + 4) % 4;
        found = true;
        break;
      }
    }

    if (!found)
    {
      nr = cr + DR[(dir + 2) % 4];
      nc = cc + DC[(dir + 2) % 4];
      if (room[nr][nc] == 2)
      {
        cr = nr;
        cc = nc;
      }
      else
        break;
    }
  }

  cout << result;

  return 0;
}
