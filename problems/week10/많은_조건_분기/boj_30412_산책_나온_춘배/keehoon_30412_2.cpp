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

  long long N, X;
  cin >> N >> X;
  vector<long long> towers(N);
  for (long long &tower : towers)
    cin >> tower;

  long long result = 1e9;

  for (int i = 0; i < N; ++i)
  {
    long long L = i > 0 ? towers[i - 1] : 2e9, I = towers[i], R = i < N - 1 ? towers[i + 1] : 2e9;
    result = min(result, max(max(L + X, R + X) - I, 0LL));
    result = min(result, max(I + X - L, 0LL) + max(I + X - R, 0LL));
    result = min(result, max(X - (I - L), 0LL) + max(X - (R - (I + max(X - (I - L), 0LL))), 0LL));
    result = min(result, max(X - (I - R), 0LL) + max(X - (L - (I + max(X - (I - R), 0LL))), 0LL));
  }

  cout << result;

  return 0;
}
