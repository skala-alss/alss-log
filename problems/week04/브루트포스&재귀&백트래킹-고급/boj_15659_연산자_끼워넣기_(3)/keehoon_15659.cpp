// 15659 – 연산자 끼워넣기 (3)
// https://www.acmicpc.net/problem/15659
// solved.ac: https://solved.ac/search?query=15659
// 시간 제한: 2 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold III
// 태그: 백트래킹, 브루트포스 알고리즘, 스택, 자료 구조
// 푼 사람 수: 496
// 평균 시도: 1.73

#include <iostream>
#include <numeric>
#include <stack>
#include <vector>
#include <unordered_map>
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

  constexpr char op[4] = {'+', '-', '*', '/'};

  int N;
  cin >> N;
  vector<int> numbers(N);
  for (int &number : numbers)
    cin >> number;
  unordered_map<char, int> ops;
  for (const char o : op)
    cin >> ops[o];

  int max_result = -1e9;
  int min_result = 1e9;

  auto precision = [](char op) -> int
  {
    if (op == '+' || op == '-')
      return 1;
    if (op == '*' || op == '/')
      return 2;
    return 0;
  };

  auto calculate = [](int a, int b, char op) -> int
  {
    if (op == '+')
      return a + b;
    if (op == '-')
      return a - b;
    if (op == '*')
      return a * b;
    if (op == '/')
      return a / b;
    return 0;
  };

  auto evaluate = [&](string expr) -> void
  {
    stack<int> values;
    stack<char> st;

    values.push(numbers[0]);

    for (int i = 0; i < expr.size(); ++i)
    {
      while (!st.empty() && precision(st.top()) >= precision(expr[i]))
      {
        int b = values.top();
        values.pop();
        int a = values.top();
        values.pop();
        char op = st.top();
        st.pop();
        values.push(calculate(a, b, op));
      }

      st.push(expr[i]);
      values.push(numbers[i + 1]);
    }

    while (!st.empty())
    {
      int b = values.top();
      values.pop();
      int a = values.top();
      values.pop();
      char op = st.top();
      st.pop();
      values.push(calculate(a, b, op));
    }

    max_result = max(max_result, values.top());
    min_result = min(min_result, values.top());
  };

  auto backtracking = [&](auto &&self, string expr) -> void
  {
    if (accumulate(ops.begin(), ops.end(), 0, [](int acc, const auto &p)
                   { return acc + p.second; }) == 0)
    {
      evaluate(expr);
      return;
    }

    for (const char &o : op)
      if (ops[o] > 0)
      {
        --ops[o];
        self(self, expr + o);
        ++ops[o];
      }
  };

  backtracking(backtracking, "");

  cout << max_result << '\n'
       << min_result;

  return 0;
}
