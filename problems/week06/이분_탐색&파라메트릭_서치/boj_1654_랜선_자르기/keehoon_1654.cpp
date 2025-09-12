// 1654 – 랜선 자르기
// https://www.acmicpc.net/problem/1654
// solved.ac: https://solved.ac/search?query=1654
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver II
// 태그: 매개 변수 탐색, 이분 탐색
// 푼 사람 수: 46,234
// 평균 시도: 4.50

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

  int K, N;
  cin >> K >> N;
  vector<long long> cables(K);
  for (long long &cable : cables)
    cin >> cable;
  long long l = 1, r = *max_element(cables.begin(), cables.end());

  int result = 0;
  while (l <= r)
  {
    long long mid = (l + r) / 2;
    long long pieces = 0;
    for (long long &cable : cables)
      pieces += cable / mid;

    if (pieces >= N)
    {
      result = mid;
      l = mid + 1;
    }

    else if (pieces < N)
      r = mid - 1;
  }

  cout << result;

  return 0;
}
