// 11723 – 집합
// https://www.acmicpc.net/problem/11723
// solved.ac: https://solved.ac/search?query=11723
// 시간 제한: 1.5 초
// 메모리 제한: 4 MB ( 하단 참고 )
// 티어: ⚪ Silver V
// 태그: 구현, 비트마스킹, 집합과 맵
// 푼 사람 수: 34,088
// 평균 시도: 3.35

#include <iostream>
#include <unordered_set>
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

  int M;
  cin >> M;

  unordered_set<int> S;

  while (M--)
  {
    string c;
    cin >> c;

    if (c == "add")
    {
      int number;
      cin >> number;
      S.insert(number);
    }
    else if (c == "remove")
    {
      int number;
      cin >> number;
      S.erase(number);
    }
    else if (c == "check")
    {
      int number;
      cin >> number;
      cout << (S.count(number) ? 1 : 0) << '\n';
    }
    else if (c == "toggle")
    {
      int number;
      cin >> number;
      if (S.count(number))
        S.erase(number);
      else
        S.insert(number);
    }
    else if (c == "all")
    {
      for (int number = 1; number <= 20; ++number)
        S.insert(number);
    }
    else if (c == "empty")
      S.clear();
  }
  return 0;
}
