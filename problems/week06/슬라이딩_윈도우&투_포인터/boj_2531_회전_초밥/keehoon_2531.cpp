// 2531 – 회전 초밥
// https://www.acmicpc.net/problem/2531
// solved.ac: https://solved.ac/search?query=2531
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver I
// 태그: 두 포인터, 브루트포스 알고리즘, 슬라이딩 윈도우
// 푼 사람 수: 8,771
// 평균 시도: 2.75

#include <iostream>
#include <vector>
#include <unordered_map>
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

  int N, d, k, c;
  cin >> N >> d >> k >> c;
  vector<int> belt(N);
  for (int &dish : belt)
    cin >> dish;

  int max_kinds = 0;
  unordered_map<int, int> sushi = {{c, 1}};
  for (int i = -k + 1; i < N; ++i)
  {
    int idx = (N + i) % N;
    ++sushi[belt[idx]];

    if (i > 0 && belt[(N + idx - k) % N] != c)
      --sushi[belt[(N + idx - k) % N]];

    if (!sushi[belt[(N + idx - k) % N]])
      sushi.erase(belt[(N + idx - k) % N]);

    if (i >= 0)
    {
      max_kinds = max(max_kinds, int(sushi.size()));
      if (max_kinds == d)
        break;
    }
  }

  cout << max_kinds;

  return 0;
}
