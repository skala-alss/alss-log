// 14888 – 연산자 끼워넣기
// https://www.acmicpc.net/problem/14888
// solved.ac: https://solved.ac/search?query=14888
// 시간 제한: 2 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver I
// 태그: 백트래킹, 브루트포스 알고리즘
// 푼 사람 수: 39,647
// 평균 시도: 2.12

#include <iostream>
#include <unordered_map>
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

  auto add = [](int a, int b) -> int
  { return a + b; };
  auto sub = [](int a, int b) -> int
  { return a - b; };
  auto mul = [](int a, int b) -> int
  { return a * b; };
  auto div = [](int a, int b) -> int
  { return a / b; };

  int N;
  cin >> N;
  vector<int> numbers(N);
  for (int &number : numbers)
    cin >> number;

  unordered_map<int (*)(int, int), int> operaters = {{add, 0}, {sub, 0}, {mul, 0}, {div, 0}};
  cin >> operaters[add];
  cin >> operaters[sub];
  cin >> operaters[mul];
  cin >> operaters[div];

  int max_val = -1 << 31;
  int min_val = (1u << 31) - 1;
  auto backtracking = [&](auto &&self, int val, int idx) -> void
  {
    if (idx == N)
    {
      max_val = max(max_val, val);
      min_val = min(min_val, val);
      return;
    }

    for (auto &kv : operaters)
      if (kv.second)
      {
        --kv.second;
        self(self, kv.first(val, numbers[idx]), idx + 1);
        ++kv.second;
      }
  };

  backtracking(backtracking, numbers[0], 1);

  cout << max_val << '\n'
       << min_val;

  return 0;
}
