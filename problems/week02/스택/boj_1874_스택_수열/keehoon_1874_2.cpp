// 1874 – 스택 수열
// https://www.acmicpc.net/problem/1874
// solved.ac: https://solved.ac/search?query=1874
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver II
// 태그: 스택, 자료 구조
// 푼 사람 수: 54,638
// 평균 시도: 2.54

#include <iostream>
#include <stack>
#include <vector>
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

  int n, target;
  stack<int> st;

  cin >> n;

  string out;
  out.reserve(4 * n);

  int next_to_push = 1;
  for (int i = 1; i <= n; ++i)
  {
    cin >> target;
    while (next_to_push <= target)
    {
      st.push(next_to_push++);
      out += "+\n";
    }

    if (!st.empty() && st.top() == target)
    {
      st.pop();
      out += "-\n";
    }

    else
    {
      out = "NO";
      break;
    }
  }

  cout << out;

  return 0;
}
