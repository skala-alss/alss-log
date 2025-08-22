// 1021 – 회전하는 큐
// https://www.acmicpc.net/problem/1021
// solved.ac: https://solved.ac/search?query=1021
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver III
// 태그: 덱, 자료 구조
// 푼 사람 수: 26,826
// 평균 시도: 1.60

#include <algorithm>
#include <iostream>
#include <deque>
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

  deque<int> dq;
  for (int i = 1; i <= N; ++i)
    dq.push_back(i);

  int pos;
  int result = 0;
  while (M--)
  {
    cin >> pos;
    int idx = 0;
    for (int i = 0; i < dq.size(); ++i)
      if (dq[i] == pos)
      {
        idx = i;
        break;
      }

    rotate(dq.begin(), dq.begin() + idx, dq.end());
    result += min(idx, (int)dq.size() - idx);
    dq.pop_front();
  }

  cout << result;
  return 0;
}
