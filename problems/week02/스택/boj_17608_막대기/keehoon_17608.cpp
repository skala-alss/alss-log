// 17608 – 막대기
// https://www.acmicpc.net/problem/17608
// solved.ac: https://solved.ac/search?query=17608
// 시간 제한: 메모리 제한
// 메모리 제한: 제출

#include <iostream>
#include <stack>
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

  int N, h;

  cin >> N;

  stack<int> stack;

  while (N--)
  {
    cin >> h;
    stack.push(h);
  }

  int highest = 0;
  int seen = 0;
  while (stack.size())
  {
    if (highest < stack.top())
    {
      highest = stack.top();
      ++seen;
    }
    stack.pop();
  }

  cout << seen;

  return 0;
}
