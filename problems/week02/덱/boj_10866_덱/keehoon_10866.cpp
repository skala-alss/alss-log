// 10866 – 덱
// https://www.acmicpc.net/problem/10866
// solved.ac: https://solved.ac/search?query=10866
// 시간 제한: 0.5 초 (추가 시간 없음)
// 메모리 제한: 256 MB
// 티어: ⚪ Silver IV
// 태그: 구현, 덱, 자료 구조
// 푼 사람 수: 46,057
// 평균 시도: 1.78

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

  deque<int> dq;
  string query;
  int number;
  while (N--)
  {
    cin >> query;
    if (query == "push_front")
    {
      cin >> number;
      dq.push_front(number);
    }

    else if (query == "push_back")
    {
      cin >> number;
      dq.push_back(number);
    }

    else if (query == "pop_front")
    {
      if (dq.empty())
        cout << -1 << '\n';
      else
      {
        cout << dq.front() << '\n';
        dq.pop_front();
      }
    }

    else if (query == "pop_back")
    {
      if (dq.empty())
        cout << -1 << '\n';
      else
      {
        cout << dq.back() << '\n';
        dq.pop_back();
      }
    }

    else if (query == "size")
      cout << dq.size() << '\n';

    else if (query == "empty")
      cout << (dq.empty() ? 1 : 0) << '\n';

    else if (query == "front")
      cout << (!dq.empty() ? dq.front() : -1) << '\n';

    else if (query == "back")
      cout << (!dq.empty() ? dq.back() : -1) << '\n';
  }
  return 0;
}
