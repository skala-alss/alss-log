// 14627 – 파닭파닭
// https://www.acmicpc.net/problem/14627
// solved.ac: https://solved.ac/search?query=14627
// 시간 제한: 2 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver II
// 태그: 매개 변수 탐색, 이분 탐색
// 푼 사람 수: 1,717
// 평균 시도: 4.44

#include <algorithm>
#include <numeric>
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

  int S, C;
  cin >> S >> C;
  vector<int> green_onions(S);
  for (int &green_onion : green_onions)
    cin >> green_onion;

  int max_len = 0;
  int l = 1, r = *max_element(green_onions.begin(), green_onions.end());
  while (l <= r)
  {
    int mid = l + (r - l) / 2;
    int cnt = 0;
    for (int &green_onion : green_onions)
      cnt += green_onion / mid;

    if (cnt >= C)
    {
      max_len = mid;
      l = mid + 1;
    }

    else if (cnt < C)
      r = mid - 1;
  }

  cout << accumulate(green_onions.begin(), green_onions.end(), 0ll) - (1ll * max_len * C);

  return 0;
}
