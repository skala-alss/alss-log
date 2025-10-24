// 2225 – 합분해
// https://www.acmicpc.net/problem/2225
// solved.ac: https://solved.ac/search?query=2225
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: 🟡 Gold V
// 태그: 다이나믹 프로그래밍, 수학
// 푼 사람 수: 18,818
// 평균 시도: 2.23

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

  vector<vector<int>> memo(N + 1, vector<int>(K + 1, 0));
  const int MOD = 1e9;

  auto dp = [&](auto &&self, int &n, int sum, int cnt) -> int
  {
    if (sum > n || cnt > K)
      return 0;

    if (memo[n][cnt] != 0)
      return memo[n][cnt];

    if (sum == n)
    {
      ++memo[n][cnt];
      return 0;
    }

    for (int i = 0; i <= n; ++i)
  };

  return 0;
}
