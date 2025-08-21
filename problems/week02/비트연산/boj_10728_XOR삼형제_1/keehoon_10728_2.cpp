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
    int N;
    cin >> N;

    vector<long long> triples;
    triples.reserve(N * N);

    for (int a = 1; a <= N; ++a)
    {
      for (int b = a + 1; b <= N; ++b)
      {
        int c = (a ^ b);
        if (c > b && c >= 1 && c <= N)
        {
          long long tmask = (1ll << (a - 1)) | (1ll << (b - 1)) | (1ll << (c - 1));
          triples.push_back(tmask);
        }
      }
    }

    long long best_mask = 0;
    int best_size = 0;

    for (long long mask = 0; mask < 1ll << N; ++mask)
    {
      int count = 0;
      int temp = mask;
      while (temp)
      {
        temp &= temp - 1;
        ++count;
      }

      if (count <= best_size)
        continue;

      bool ok = true;
      for (long long tmask : triples)
      {
        if ((mask & tmask) == tmask)
        {
          ok = false;
          break;
        }
      }
      if (!ok)
        continue;

      best_size = count;
      best_mask = mask;
    }

    cout << best_size << '\n';
    bool first = true;
    for (int v = 1; v <= N; ++v)
    {
      if (best_mask & (1ll << (v - 1)))
      {
        if (!first)
          cout << ' ';
        cout << v;
        first = false;
      }
    }
    cout << '\n';
  }
  return 0;
}