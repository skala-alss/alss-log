// 10828 – 스택
// https://www.acmicpc.net/problem/10828
// solved.ac: https://solved.ac/search?query=10828
// 시간 제한: 0.5 초 (추가 시간 없음)
// 메모리 제한: 256 MB
// 티어: ⚪ Silver IV
// 태그: 구현, 스택, 자료 구조
// 푼 사람 수: 84,114
// 평균 시도: 2.58

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

  int N, number;
  string query;
  stack<int> st;

  cin >> N;

  for (int i = 1; i <= N; ++i)
  {
    cin >> query;

    if (query == "push")
    {
      cin >> number;
      st.push(number);
    }

    else if (query == "pop")
    {
      if (st.size())
      {
        cout << st.top() << '\n';
        st.pop();
      }
      else
        cout << -1 << '\n';
    }

    else if (query == "size")
      cout << st.size() << '\n';

    else if (query == "empty")
      cout << (st.empty() ? 1 : 0) << '\n';

    else if (query == "top")
      cout << (st.size() ? st.top() : -1) << '\n';
  }
  return 0;
}
