// 2161 – 카드1
// https://www.acmicpc.net/problem/2161
// solved.ac: https://solved.ac/search?query=2161
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver V
// 태그: 구현, 자료 구조, 큐
// 푼 사람 수: 12,913
// 평균 시도: 1.46

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
  queue<int> q;

  cin >> N;

  for (int i = 1; i <= N; ++i)
  {
    q.push(i);
  }

  while (!q.empty())
  {
    cout << q.front() << ' ';
    q.pop();
    if (!q.empty())
    {
      q.push(q.front());
      q.pop();
    }
  }
  return 0;
}
