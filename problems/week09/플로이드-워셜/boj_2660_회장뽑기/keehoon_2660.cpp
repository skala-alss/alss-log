// 2660 – 회장뽑기
// https://www.acmicpc.net/problem/2660
// solved.ac: https://solved.ac/search?query=2660
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: 🟡 Gold V
// 태그: 그래프 이론, 그래프 탐색, 너비 우선 탐색, 최단 경로, 플로이드–워셜
// 푼 사람 수: 6,949
// 평균 시도: 1.74

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
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

  vector<vector<int>> dp(N + 1, vector<int>(N + 1, 1e9));
  while (true)
  {
    int m1, m2;
    cin >> m1 >> m2;
    if (m1 == -1 && m2 == -1)
      break;

    dp[m1][m2] = 1;
    dp[m2][m1] = 1;
  }

  for (int k = 0; k <= N; ++k)
    for (int i = 0; i <= N; ++i)
      for (int j = 0; j <= N; ++j)
        if (i != j && dp[i][j] > dp[i][k] + dp[k][j])
          dp[i][j] = dp[i][k] + dp[k][j];

  map<int, set<int>> result;
  for (int i = 1; i <= N; ++i)
  {
    auto it_max = max_element(dp[i].begin(), dp[i].end());
    auto it_second = max_element(
        dp[i].begin(), dp[i].end(),
        [it_max](int a, int b)
        {
          if (a == *it_max)
            return true;
          if (b == *it_max)
            return false;
          return a < b;
        });

    result[*it_second].insert(i);
  }

  cout << result.begin()->first << ' ' << result.begin()->second.size() << '\n';
  for (const int &candidate : result.begin()->second)
    cout << candidate << ' ';

  return 0;
}
