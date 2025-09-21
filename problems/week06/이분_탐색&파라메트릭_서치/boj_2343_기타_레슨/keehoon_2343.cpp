// 2343 – 기타 레슨
// https://www.acmicpc.net/problem/2343
// solved.ac: https://solved.ac/search?query=2343
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver I
// 태그: 매개 변수 탐색, 이분 탐색
// 푼 사람 수: 11,828
// 평균 시도: 2.92

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

  int N, M;
  cin >> N >> M;
  vector<int> blu_rays(N);
  long long l = 1, r = 0;
  for (int &blu_ray : blu_rays)
  {
    cin >> blu_ray;
    l = max((int)l, blu_ray);
    r += blu_ray;
  }

  long long best_len = 0;
  while (l <= r)
  {
    long long mid = (l + r) / 2;
    int tmp = 0, cnt = 0;
    for (int &blu_ray : blu_rays)
    {
      tmp += blu_ray;

      if (tmp >= mid)
      {
        ++cnt;
        tmp = tmp > mid ? blu_ray : 0;
      }
    }

    if (tmp)
      ++cnt;

    if (cnt <= M)
    {
      best_len = mid;
      r = mid - 1;
    }

    else if (cnt > M)
      l = mid + 1;
  }

  cout << best_len;

  return 0;
}
