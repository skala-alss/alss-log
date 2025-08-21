// 18258 – 큐 2
// https://www.acmicpc.net/problem/18258
// solved.ac: https://solved.ac/search?query=18258
// 시간 제한: 1 초 ( 하단 참고 )
// 메모리 제한: 512 MB
// 티어: ⚪ Silver IV
// 태그: 자료 구조, 큐
// 푼 사람 수: 34,928
// 평균 시도: 2.99

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
  string query;
  string result;

  cin >> N;

  while (N--)
  {
    cin >> query;

    if (query == "push")
    {
      int number;
      cin >> number;
      q.push(number);
    }

    else if (query == "pop")
    {
      if (q.empty())
      {
        result += "-1\n";
      }
      else
      {
        result += to_string(q.front()) + '\n';
        q.pop();
      }
    }

    else if (query == "size")
      result += to_string(q.size()) + "\n";

    else if (query == "empty")
      result += q.empty() ? to_string(1) + "\n" : to_string(0) + "\n";

    else if (query == "front")
      result += !q.empty() ? to_string(q.front()) + "\n" : to_string(-1) + "\n";

    else if (query == "back")
      result += !q.empty() ? to_string(q.back()) + "\n" : to_string(-1) + "\n";
  }

  cout << result;

  return 0;
}
