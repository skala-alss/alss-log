// 10728 – XOR삼형제 1
// https://www.acmicpc.net/problem/10728
// solved.ac: https://solved.ac/search?query=10728
// 시간 제한: 5 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver I
// 태그: 브루트포스 알고리즘, 비트마스킹, 해 구성하기
// 푼 사람 수: 221
// 평균 시도: 2.20

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

  int T;
  cin >> T;

  while (T--)
  {
    long long N;
    cin >> N;

    int k = 0;
    while ((1LL << (k + 1)) <= N)
      ++k;
    long long P = 1LL << k;                       // 2^k
    long long H = 1LL << (k - 1 < 0 ? 0 : k - 1); // 2^{k-1} (k=0일 때 1로 처리)

    long long L = H;
    long long R = min(N, P + H - 1); // [H, min(N, 2^k+2^{k-1}-1)]
    long long sz = R - L + 1;        // = min(P, N - H + 1)

    cout << sz << '\n';
    for (long long x = L; x <= R; ++x)
    {
      cout << x << (x == R ? '\n' : ' ');
    }
  }
  return 0;
}