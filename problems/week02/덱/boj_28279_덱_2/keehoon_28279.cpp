// 28279 – 덱 2
// https://www.acmicpc.net/problem/28279
// solved.ac: https://solved.ac/search?query=28279
// 시간 제한: 2 초
// 메모리 제한: 1024 MB
// 티어: ⚪ Silver IV
// 태그: 덱, 자료 구조
// 푼 사람 수: 10,375
// 평균 시도: 1.98

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

  int N, query, X;
  deque<int> dq;

  cin >> N;

  while (N--)
  {
    cin >> query;

    if (query == 1)
    {
      cin >> X;
      dq.push_front(X);
    }

    else if (query == 2)
    {
      cin >> X;
      dq.push_back(X);
    }

    else if (query == 3)
    {
      if (dq.empty())
        cout << -1 << '\n';
      else
      {
        cout << dq.front() << '\n';
        dq.pop_front();
      }
    }

    else if (query == 4)
    {
      if (dq.empty())
        cout << -1 << '\n';
      else
      {
        cout << dq.back() << '\n';
        dq.pop_back();
      }
    }

    else if (query == 5)
      cout << dq.size() << '\n';

    else if (query == 6)
      cout << (dq.empty() ? 1 : 0) << '\n';

    else if (query == 7)
    {
      if (dq.empty())
        cout << -1 << '\n';
      else
        cout << dq.front() << '\n';
    }

    else if (query == 8)
    {
      if (dq.empty())
        cout << -1 << '\n';
      else
        cout << dq.back() << '\n';
    }
  }
  return 0;
}
