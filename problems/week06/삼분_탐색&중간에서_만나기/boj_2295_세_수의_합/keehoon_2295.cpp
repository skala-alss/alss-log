// 2295 – 세 수의 합
// https://www.acmicpc.net/problem/2295
// solved.ac: https://solved.ac/search?query=2295
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: 🟡 Gold IV
// 태그: 이분 탐색, 자료 구조, 중간에서 만나기, 해시를 사용한 집합과 맵
// 푼 사람 수: 4,539
// 평균 시도: 3.41

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

  int N;
  cin >> N;

  vector<int> sequence(N), sums;
  sums.reserve((N * (N + 1)) / 2);

  for (int &term : sequence)
    cin >> term;

  sort(sequence.begin(), sequence.end());
  for (int i = 0; i < N; ++i)
    for (int j = i; j < N; ++j)
      sums.push_back(sequence[i] + sequence[j]);

  sort(sums.begin(), sums.end());
  for (int i = N - 1; i > 0; --i)
    for (int j = i; j >= 0; --j)
    {
      int diff = sequence[i] - sequence[j];
      if (binary_search(sums.begin(), sums.end(), diff))
      {
        cout << sequence[i];
        return 0;
      }
    }

  return 0;
}
