// 12605 – 단어순서 뒤집기
// https://www.acmicpc.net/problem/12605
// solved.ac: https://solved.ac/search?query=12605
// 시간 제한: 메모리 제한
// 메모리 제한: 제출
// 티어: 🟫 Bronze II
// 태그: 구현, 문자열, 스택, 자료 구조, 파싱
// 푼 사람 수: 5,121
// 평균 시도: 1.63

#include <iostream>
#if defined(_WIN32)
#include <io.h>
#include <cstdio>
#else
#include <unistd.h>
#include <cstdio>
#endif
#include <stack>

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
  string line;

  cin >> N;
  cin.ignore();

  stack<string> stack;

  for (int i = 1; i <= N; ++i)
  {
    getline(cin, line);
    size_t s = 0;
    size_t e = 0;
    while (e < line.length() + 1)
    {
      while (!isspace(line[e]))
        ++e;

      stack.push(line.substr(s, e - s));
      ++e;
      s = e;
    }

    cout << "Case #" << i << ": ";
    while (stack.size())
    {
      cout << stack.top() << ' ';
      stack.pop();
    }
    cout << '\n';
  }
  return 0;
}
