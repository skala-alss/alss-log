// 15649 – N과 M (1)
// https://www.acmicpc.net/problem/15649
// solved.ac: https://solved.ac/search?query=15649
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver III
// 태그: 백트래킹
// 푼 사람 수: 56,949
// 평균 시도: 1.58

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
  vector<bool> used(N + 1);
  vector<int> sequence;

  auto permutations = [&](auto &&self, vector<int> &permutation) -> void
  {
    if (permutation.size() == M)
    {
      for (int term : permutation)
        cout << term << ' ';
      cout << '\n';
      return;
    }

    for (int i = 1; i <= N; ++i)
    {
      if (!used[i])
      {
        used[i] = true;
        permutation.push_back(i);
        self(self, permutation);
        used[i] = false;
        permutation.pop_back();
      }
    }
  };

  permutations(permutations, sequence);

  return 0;
}
