// 6236 – 용돈 관리
// https://www.acmicpc.net/problem/6236
// solved.ac: https://solved.ac/search?query=6236
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver I
// 태그: 매개 변수 탐색, 이분 탐색
// 푼 사람 수: 5,633
// 평균 시도: 3.36

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
  vector<int> amounts(N);
  int l = 1, r = 1e9;
  for (int &amount : amounts)
  {
    cin >> amount;
    l = max(l, amount);
  }

  int best_amount;
  while (l <= r)
  {
    int mid = (l + r) / 2;
    int loadout = 0, cnt = 0;
    for (int &amount : amounts)
    {
      if (loadout < amount)
      {
        loadout = mid;
        ++cnt;
      }

      loadout -= amount;
    }

    if (cnt <= M)
    {
      best_amount = mid;
      r = mid - 1;
    }

    else
      l = mid + 1;
  }

  cout << best_amount;

  return 0;
}
