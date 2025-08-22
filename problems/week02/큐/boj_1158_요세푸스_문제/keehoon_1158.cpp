// 1158 – 요세푸스 문제
// https://www.acmicpc.net/problem/1158
// solved.ac: https://solved.ac/search?query=1158
// 시간 제한: 2 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver IV
// 태그: 구현, 자료 구조, 큐
// 푼 사람 수: 48,515
// 평균 시도: 2.02

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

  int N, K;
  cin >> N >> K;

  queue<int> q;

  for (int i = 1; i <= N; ++i)
    q.push(i);

  string result = "<";

  while (!q.empty())
  {
    if (result.length() != 1)
      result += ", ";

    for (int i = 0; i < K - 1; ++i)
    {
      q.push(q.front());
      q.pop();
    }

    result += to_string(q.front());
    q.pop();
  }

  cout << result + ">";

  return 0;
}
