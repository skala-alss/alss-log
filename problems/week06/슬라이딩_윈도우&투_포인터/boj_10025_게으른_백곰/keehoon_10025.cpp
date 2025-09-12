// 10025 – 게으른 백곰
// https://www.acmicpc.net/problem/10025
// solved.ac: https://solved.ac/search?query=10025
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver III
// 태그: 누적 합, 두 포인터, 슬라이딩 윈도우
// 푼 사람 수: 2,295
// 평균 시도: 3.27

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

  int N, K;
  cin >> N >> K;
  vector<int> coordinates(1e6 + 1);

  while (N--)
  {
    int gi, xi;
    cin >> gi >> xi;
    coordinates[xi] = gi;
  }

  int ices = 0;
  int window = 0;
  int sz = 2 * K + 1;
  for (int i = 0; i < 1e6 + 1; ++i)
  {
    window += i >= sz ? coordinates[i] - coordinates[i - sz] : coordinates[i];
    ices = max(ices, window);
  }

  cout << ices;

  return 0;
}
