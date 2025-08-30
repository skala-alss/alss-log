// 15663 – N과 M (9)
// https://www.acmicpc.net/problem/15663
// solved.ac: https://solved.ac/search?query=15663
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver II
// 태그: 백트래킹
// 푼 사람 수: 22,191
// 평균 시도: 2.02

#include <iostream>
#include <map>
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

  map<int, int> counter;
  for (int i = 0; i < N; ++i)
  {
    int number;
    cin >> number;
    ++counter[number];
  }

  vector<int> permutation;
  permutation.reserve(M);

  auto permutations = [&](auto &&self) -> void
  {
    if (permutation.size() == M)
    {
      for (int &term : permutation)
        cout << term << ' ';
      cout << '\n';
      return;
    }

    for (auto &[val, cnt] : counter)
      if (cnt > 0)
      {
        --counter[val];
        permutation.push_back(val);
        self(self);
        ++counter[val];
        permutation.pop_back();
      }
  };

  permutations(permutations);
  return 0;
}
