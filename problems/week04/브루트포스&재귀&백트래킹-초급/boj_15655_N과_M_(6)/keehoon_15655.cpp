// 15655 – N과 M (6)
// https://www.acmicpc.net/problem/15655
// solved.ac: https://solved.ac/search?query=15655
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver III
// 태그: 백트래킹
// 푼 사람 수: 19,966
// 평균 시도: 1.19

#include <algorithm>
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

  int N, M;
  cin >> N >> M;

  vector<int> sequence(N);
  for (int i = 0; i < N; ++i)
  {
    int number;
    cin >> number;
    sequence[i] = number;
  }
  sort(sequence.begin(), sequence.begin() + N);

  vector<int> combination;
  combination.reserve(M);
  auto combinations = [&](auto &&self, int start) -> void
  {
    if (combination.size() == M)
    {
      for (int &term : combination)
        cout << term << ' ';
      cout << '\n';
    }

    for (int i = start; i < N; ++i)
    {
      combination.push_back(sequence[i]);
      self(self, i + 1);
      combination.pop_back();
    }
  };

  combinations(combinations, 0);
  return 0;
}
