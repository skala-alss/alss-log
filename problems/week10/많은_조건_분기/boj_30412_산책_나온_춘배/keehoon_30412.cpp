// 30412 – 산책 나온 춘배
// https://www.acmicpc.net/problem/30412
// solved.ac: https://solved.ac/search?query=30412
// 시간 제한: 1 초
// 메모리 제한: 1024 MB
// 티어: 🟡 Gold V
// 태그: 구현, 많은 조건 분기, 브루트포스 알고리즘
// 푼 사람 수: 84
// 평균 시도: 2.63

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

  int N, X;
  cin >> N >> X;
  vector<int> towers(N);
  for (int &tower : towers)
    cin >> tower;

  int result = 1e9;
  for (int i = 0; i < N; ++i)
  {
    if (i == 0)
      result = min(result, max(X - abs(towers[0] - towers[1]), 0));
    else if (i == N - 1)
      result = min(result, max(X - abs(towers[N - 1] - towers[N - 2]), 0));
    else
    {
      int L = towers[i - 1], I = towers[i], R = towers[i + 1];
      result = min(result, max(0, max(L + X, R + X) - I));
      result = min(result, max(0, I + X - L) + max(0, I + X - R));
      result = min(result, L >= R + 2 * X ? max(0, R + X - I) : 2 * max(R + X, L - X) - I + X - L);
      result = min(result, L <= R - 2 * X ? max(0, L + X - I) : 2 * max(L + X, R - X) - I + X - R);
    }
  }

  cout << result;

  return 0;
}
