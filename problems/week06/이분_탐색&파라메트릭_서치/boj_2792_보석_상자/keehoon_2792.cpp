// 2792 – 보석 상자
// https://www.acmicpc.net/problem/2792
// solved.ac: https://solved.ac/search?query=2792
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver I
// 태그: 매개 변수 탐색, 이분 탐색
// 푼 사람 수: 3,660
// 평균 시도: 2.44

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
  vector<int> jewels(M);
  int l = 1, r = 0;
  for (int &jewel : jewels)
  {
    cin >> jewel;
    r = max(r, jewel);
  }

  int best = r;
  while (l <= r)
  {
    int mid = l + (r - l) / 2;
    int need = 0;
    for (int &jewel : jewels)
      need += (jewel + mid - 1) / mid;

    if (need <= N)
    {
      best = mid;
      r = mid - 1;
    }

    else if (need > N)
      l = mid + 1;
  }

  cout << best;

  return 0;
}
