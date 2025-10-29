// 2294 – 동전 2
// https://www.acmicpc.net/problem/2294
// solved.ac: https://solved.ac/search?query=2294
// 시간 제한: 1 초 (추가 시간 없음)
// 메모리 제한: 128 MB
// 티어: 🟡 Gold V
// 태그: 다이나믹 프로그래밍
// 푼 사람 수: 20,696
// 평균 시도: 3.25

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

  int n, k;
  cin >> n >> k;
  vector<int> coins(n);
  for (int &coin : coins)
    cin >> coin;

  sort(coins.begin(), coins.end(), [&](const int &a, const int &b)
       { return a > b; });

  vector<int> dp(k + 1, 1e8);

  dp[0] = 0;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j <= k; ++j)
      if (j + coins[i] <= k)
        dp[j + coins[i]] = min(dp[j + coins[i]], dp[j] + 1);

  cout << (dp[k] != 1e8 ? dp[k] : -1);

  return 0;
}
