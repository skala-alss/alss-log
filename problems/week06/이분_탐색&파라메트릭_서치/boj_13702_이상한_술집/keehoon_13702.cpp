// 13702 – 이상한 술집
// https://www.acmicpc.net/problem/13702
// solved.ac: https://solved.ac/search?query=13702
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver II
// 태그: 매개 변수 탐색, 이분 탐색
// 푼 사람 수: 2,064
// 평균 시도: 3.30

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

  int N, K;
  cin >> N >> K;
  vector<int> kettles(N);
  for (int &kettle : kettles)
    cin >> kettle;

  int max_vol = 0;
  long long l = 0, r = *max_element(kettles.begin(), kettles.end());
  while (l <= r)
  {
    int mid = (l + r) / 2;
    int glasses = 0;
    for (int &kettle : kettles)
      glasses += mid ? kettle / mid : 1;

    if (glasses >= K)
    {
      max_vol = mid;
      l = mid + 1;
    }
    else if (glasses < K)
      r = mid - 1;
  }

  cout << max_vol;

  return 0;
}
