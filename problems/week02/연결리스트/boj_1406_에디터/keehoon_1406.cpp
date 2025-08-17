// 1406 – 에디터
// https://www.acmicpc.net/problem/1406
// solved.ac: https://solved.ac/search?query=1406
// 시간 제한: 0.3 초 ( 하단 참고 )
// 메모리 제한: 512 MB
// 티어: ⚪ Silver II
// 태그: 스택, 연결 리스트, 자료 구조
// 푼 사람 수: 28,821
// 평균 시도: 3.64

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

  string s;
  cin >> s;
  list<char> li(s.begin(), s.end());

  int M;
  cin >> M;

  auto it = li.end();
  while (M--)
  {
    char order;
    cin >> order;

    if (order == 'L')
    {
      if (it != li.begin())
        it = prev(it);
    }
    else if (order == 'D')
    {
      if (it != li.end())
        it = next(it);
    }
    else if (order == 'B')
    {
      if (it != li.begin())
        li.erase(prev(it));
    }
    else if (order == 'P')
    {
      char x;
      cin >> x;
      li.insert(it, x);
    }
  }
  for (char letter : li)
    cout << letter;
  return 0;
}
