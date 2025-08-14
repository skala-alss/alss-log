// 11286 – 절댓값 힙
// https://www.acmicpc.net/problem/11286
// solved.ac: https://solved.ac/search?query=11286
// 시간 제한: 1 초 (추가 시간 없음) ( 하단 참고 )
// 메모리 제한: 256 MB
// 티어: ⚪ Silver I
// 태그: 우선순위 큐, 자료 구조
// 푼 사람 수: 33,550
// 평균 시도: 1.74

#include <iostream>
#include <queue>
#if defined(_WIN32)
#include <io.h>
#include <cstdio>
#else
#include <unistd.h>
#include <cstdio>
#endif

using namespace std;

struct Compare
{
  bool operator()(const int &a, const int &b) const
  {
    if (abs(a) != abs(b))
      return abs(a) > abs(b);
    return a > b;
  }
};

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

  int N, x;

  cin >> N;

  priority_queue<int, vector<int>, Compare> pq;

  while (N--)
  {
    cin >> x;

    if (x)
      pq.push(x);

    else
    {
      if (pq.empty())
        cout << 0 << '\n';
      else
      {
        cout << pq.top() << '\n';
        pq.pop();
      }
    }
  }
  return 0;
}
