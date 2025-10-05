// 1912 – 연속합
// https://www.acmicpc.net/problem/1912
// solved.ac: https://solved.ac/search?query=1912
// 시간 제한: 1 초 (추가 시간 없음)
// 메모리 제한: 128 MB
// 티어: ⚪ Silver II
// 태그: 다이나믹 프로그래밍, 최대 부분 배열 문제
// 푼 사람 수: 47,129
// 평균 시도: 2.62

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
  vector<int> dp(n);

  int result = -1000;
  for (int i = 0; i < n; ++i)
  {
    cin >> dp[i];
    if (i > 0)
      dp[i] = max(dp[i], dp[i] + dp[i - 1]);

    result = max(result, dp[i]);
  }

  cout << result;

  return 0;
}
