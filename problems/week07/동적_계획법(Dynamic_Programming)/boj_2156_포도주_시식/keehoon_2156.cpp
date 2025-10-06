// 2156 – 포도주 시식
// https://www.acmicpc.net/problem/2156
// solved.ac: https://solved.ac/search?query=2156
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver I
// 태그: 다이나믹 프로그래밍
// 푼 사람 수: 42,266
// 평균 시도: 3.02

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

  int n;
  cin >> n;
  vector<vector<int>> dp(2, vector<int>(n));

  int t0 = 0;    // i만 고름
  int t1 = 0;    // i-1도 고름
  int best1 = 0; // i-1까지의 최선
  int best2 = 0; // i-2까지의 최선

  for (int i = 0; i < n; ++i)
  {
    int vol;
    cin >> vol;

    int new_t0 = best2 + vol;
    int new_t1 = t0 + vol;

    best2 = best1;
    best1 = max({best1, new_t0, new_t1});
    t0 = new_t0;
    t1 = new_t1;
  }

  cout << best1;

  return 0;
}
