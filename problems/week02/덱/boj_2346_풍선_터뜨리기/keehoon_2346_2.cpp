// 2346 – 풍선 터뜨리기
// https://www.acmicpc.net/problem/2346
// solved.ac: https://solved.ac/search?query=2346
// 시간 제한: 2 초
// 메모리 제한: 4 MB
// 티어: ⚪ Silver III
// 태그: 덱, 자료 구조
// 푼 사람 수: 16,014
// 평균 시도: 2.25

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

  int N;
  cin >> N;

  deque<pair<int, int>> dq;

  for (int i = 1; i <= N; ++i)
  {
    int number;
    cin >> number;
    dq.push_back(make_pair(number, i));
  }

  while (!dq.empty())
  {
    auto [move, idx] = dq.front();
    dq.pop_front();
    cout << idx << ' ';

    int n = dq.size();
    if (n == 0)
      break;

    if (move > 0)
    {
      move = (move - 1) % n;
      rotate(dq.begin(), dq.begin() + move, dq.end());
    }
    else
    {
      move = (-move) % n;
      rotate(dq.begin(), dq.end() - move, dq.end());
    }
  }
  return 0;
}
