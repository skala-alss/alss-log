// 5397 – 키로거
// https://www.acmicpc.net/problem/5397
// solved.ac: https://solved.ac/search?query=5397
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver II
// 태그: 스택, 연결 리스트, 자료 구조
// 푼 사람 수: 15,114
// 평균 시도: 3.47

#include <iostream>
#include <list>
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

  int T;
  cin >> T;

  while (T--)
  {
    string L;
    cin >> L;
    list<char> li;

    auto current = li.begin();
    for (char l : L)
    {
      if (l == '<')
      {
        if (current != li.begin())
          current = prev(current);
      }
      else if (l == '>')
      {
        if (current != li.end())
          current = next(current);
      }
      else if (l == '-')
      {
        if (current != li.begin())
          li.erase(prev(current));
      }
      else
        li.insert(current, l);
    }
    for (char l : li)
      cout << l;
    cout << '\n';
  }
  return 0;
}
