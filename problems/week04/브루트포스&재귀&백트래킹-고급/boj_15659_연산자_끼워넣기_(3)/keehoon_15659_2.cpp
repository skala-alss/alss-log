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

  int N;
  cin >> N;
  vector<int> numbers(N);
  for (int &number : numbers)
    cin >> number;
  int ops[4];
  for (int &op : ops)
    cin >> op;

  int max_result = -1e9;
  int min_result = 1e9;

  auto dfs = [&](auto &&self, int idx, int sum, int cur) -> void
  {
    if (idx == N)
    {
      max_result = max(max_result, sum + cur);
      min_result = min(min_result, sum + cur);
      return;
    }

    if (ops[0] > 0)
    {
      --ops[0];
      self(self, idx + 1, sum + cur, numbers[idx]);
      ++ops[0];
    }

    if (ops[1] > 0)
    {
      --ops[1];
      self(self, idx + 1, sum + cur, -numbers[idx]);
      ++ops[1];
    }

    if (ops[2] > 0)
    {
      --ops[2];
      self(self, idx + 1, sum, cur * numbers[idx]);
      ++ops[2];
    }

    if (ops[3] > 0)
    {
      --ops[3];
      self(self, idx + 1, sum, cur / numbers[idx]);
      ++ops[3];
    }
  };

  dfs(dfs, 1, 0, numbers[0]);

  cout << max_result << '\n'
       << min_result;

  return 0;
}
