// 29793 – 라라와 용맥 변환
// https://www.acmicpc.net/problem/29793
// solved.ac: https://solved.ac/search?query=29793
// 시간 제한: 1 초
// 메모리 제한: 1024 MB
// 티어: 🟡 Gold III
// 태그: 다이나믹 프로그래밍, 많은 조건 분기, 문자열, 브루트포스 알고리즘, 애드 혹
// 푼 사람 수: 130
// 평균 시도: 3.34

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

  int N, H;
  string S;
  cin >> N >> H >> S;

  constexpr char LETTERS[3] = {'S', 'R', 'W'};

  const int BIG_NUM = 1e9;

  if (H >= 4)
  {
    if (N >= 4)
    {
      cout << -1;
      return 0;
    }

    vector<bool> used(26, false);
    int kinds = 0;
    for (const char &letter : S)
      if (!used[letter - 'A'])
      {
        used[letter - 'A'] = true;
        ++kinds;
      }

    cout << N - kinds;
    return 0;
  }

  const int H1 = H + 1;
  const int STRIDE_R = H1;
  const int STRIDE_S = H1 * H1;
  const int STATE_COUNT = H1 * H1 * H1;

  vector<int> dp_prev(STATE_COUNT, BIG_NUM), dp_cur(STATE_COUNT, BIG_NUM);

  dp_prev[0] = 0;

  for (int i = 0; i < N; ++i)
  {
    fill(dp_cur.begin(), dp_cur.end(), BIG_NUM);

    for (int s = 0; s <= H; ++s)
      for (int r = 0; r <= H; ++r)
        for (int w = 0; w <= H; ++w)
        {
          int prv = s * STRIDE_S + r * STRIDE_R + w;
          int base = dp_prev[prv];
          if (base == BIG_NUM)
            continue;

          int nxt_s = s == 0 ? 0 : min(s + 1, H);
          int nxt_r = r == 0 ? 0 : min(r + 1, H);
          int nxt_w = w == 0 ? 0 : min(w + 1, H);

          if (s == 0 || s == H)
          {
            int ns = 1, nr = nxt_r, nw = nxt_w;
            int idx = ns * STRIDE_S + nr * STRIDE_R + nw;
            dp_cur[idx] = min(dp_cur[idx], base + (S[i] == 'S' ? 0 : 1));
          }

          if (r == 0 || r == H)
          {
            int ns = nxt_s, nr = 1, nw = nxt_w;
            int idx = ns * STRIDE_S + nr * STRIDE_R + nw;
            dp_cur[idx] = min(dp_cur[idx], base + (S[i] == 'R' ? 0 : 1));
          }

          if (w == 0 || w == H)
          {
            int ns = nxt_s, nr = nxt_r, nw = 1;
            int idx = ns * STRIDE_S + nr * STRIDE_R + nw;
            dp_cur[idx] = min(dp_cur[idx], base + (S[i] == 'W' ? 0 : 1));
          }
        }

    dp_prev.swap(dp_cur);
  }

  int result = *min_element(dp_prev.begin(), dp_prev.end());

  cout << (result != BIG_NUM ? result : -1);

  return 0;
}
