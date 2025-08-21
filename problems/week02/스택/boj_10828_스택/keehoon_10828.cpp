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
#include <deque>
#include <sstream>

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

  cin >> N;
  cin.ignore();

  deque<int> st;
  string line;

  for (int i = 1; i <= N; ++i)
  {
    getline(cin, line);
    stringstream query(line);
    string order;

    query >> order;

    if (order == "push")
    {
      int number;
      query >> number;
      st.push_back(number);
    }

    else if (order == "pop")
    {
      if (st.size())
      {
        cout << st.back() << '\n';
        st.pop_back();
      }
      else
        cout << -1 << '\n';
    }

    else if (order == "size")
      cout << st.size() << '\n';

    else if (order == "empty")
      cout << (st.size() ? 0 : 1) << '\n';

    else if (order == "top")
      cout << (st.size() ? st.back() : -1) << '\n';
  }

  return 0;
}
