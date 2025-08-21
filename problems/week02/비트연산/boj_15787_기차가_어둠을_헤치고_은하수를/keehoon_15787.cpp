// 15787 – 기차가 어둠을 헤치고 은하수를
// https://www.acmicpc.net/problem/15787
// solved.ac: https://solved.ac/search?query=15787
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver II
// 태그: 구현, 비트마스킹
// 푼 사람 수: 2,322
// 평균 시도: 3.35

#include <iostream>
#include <unordered_set>
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

  vector<int> trains(N + 1, 0);
  unordered_set<int> passed;
  passed.reserve(N * 2);

  while (M--)
  {
    int order, train;
    cin >> order >> train;

    if (order == 1)
    {
      int seat;
      cin >> seat;

      trains[train] |= 1 << seat - 1;
    }

    else if (order == 2)
    {
      int seat;
      cin >> seat;

      trains[train] &= ~(1 << seat - 1);
    }

    else if (order == 3)
    {
      trains[train] <<= 1;
      trains[train] &= ~(1 << 20);
    }

    else if (order == 4)
      trains[train] >>= 1;
  }

  for (int i = 1; i <= N; ++i)
    passed.insert(trains[i]);

  cout << passed.size();
  return 0;
}
