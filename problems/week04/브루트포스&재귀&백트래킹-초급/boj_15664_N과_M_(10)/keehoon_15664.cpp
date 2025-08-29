// 15664 – N과 M (10)
// https://www.acmicpc.net/problem/15664
// solved.ac: https://solved.ac/search?query=15664
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver II
// 태그: 백트래킹
// 푼 사람 수: 13,225
// 평균 시도: 1.26

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
  for (int i = 1; i <= N; ++i)
  {
    int number;
    cin >> number;
    ++counter[number];
  }

  vector<int> indices;
  indices.reserve(counter.size());
  for (auto &kv : counter)
    indices.push_back(kv.first);
  int elements = indices.size();

  vector<int> combination;
  combination.reserve(M);
  auto combinations = [&](auto &&self, int start) -> void
  {
    if (combination.size() == M)
    {
      for (int &term : combination)
        cout << term << ' ';
      cout << '\n';
      return;
    }

    for (int i = start; i < elements; ++i)
      if (counter[indices[i]] > 0)
      {
        --counter[indices[i]];
        combination.push_back(indices[i]);
        self(self, i);
        ++counter[indices[i]];
        combination.pop_back();
      }
  };

  combinations(combinations, 0);
  return 0;
}
