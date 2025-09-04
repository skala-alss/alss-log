// 7662 – 이중 우선순위 큐
// https://www.acmicpc.net/problem/7662
// solved.ac: https://solved.ac/search?query=7662
// 시간 제한: 6 초
// 메모리 제한: 256 MB
// 티어: 🟡 Gold IV
// 태그: 우선순위 큐, 자료 구조, 집합과 맵, 트리를 사용한 집합과 맵
// 푼 사람 수: 15,332
// 평균 시도: 4.40

#include <iostream>
#include <set>
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

  multiset<int> q;
  while (T--)
  {
    int k;
    cin >> k;

    while (k--)
    {
      char c;
      int n;
      cin >> c >> n;

      if (c == 'I')
        q.insert(n);
      else if (c == 'D' && !q.empty())
        n == 1 ? q.erase(prev(q.end())) : q.erase(q.begin());
    }

    cout << (!q.empty() ? to_string(*q.rbegin()) + " " + to_string(*q.begin()) : "EMPTY") << '\n';
    q.clear();
  }
  return 0;
}
