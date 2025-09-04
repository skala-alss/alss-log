// 1918 – 후위 표기식
// https://www.acmicpc.net/problem/1918
// solved.ac: https://solved.ac/search?query=1918
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: 🟡 Gold II
// 태그: 스택, 자료 구조
// 푼 사람 수: 17,714
// 평균 시도: 2.57

#include <algorithm>
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

  string inorder;
  cin >> inorder;

  int tokens = inorder.length();
  stack<char> st;
  vector<char> postorder;
  postorder.reserve(tokens);

  vector<char> additiveOps = {'+', '-'};
  vector<char> multiplicativeOps = {'*', '/'};
  for (char &token : inorder)
  {
    if ('A' <= token && token <= 'Z')
    {
      postorder.push_back(token);
    }
    else if ((find(multiplicativeOps.begin(), multiplicativeOps.end(), token) !=
              multiplicativeOps.end()))
    {
      while (!st.empty() &&
             (find(multiplicativeOps.begin(), multiplicativeOps.end(), st.top()) !=
              multiplicativeOps.end()))
      {
        postorder.push_back(st.top());
        st.pop();
      }
      st.push(token);
    }
    else if (find(additiveOps.begin(), additiveOps.end(), token) !=
             additiveOps.end())
    {
      while (!st.empty() && st.top() != '(')
      {
        postorder.push_back(st.top());
        st.pop();
      }
      st.push(token);
    }
    else if (token == '(')
      st.push(token);
    else if (token == ')')
    {
      while (!st.empty() && st.top() != '(')
      {
        postorder.push_back(st.top());
        st.pop();
      }
      st.pop();
    }
  }

  while (st.size())
  {
    postorder.push_back(st.top());
    st.pop();
  }

  for (char &token : postorder)
    cout << token;
  return 0;
}
