// 29793 – 라라와 용맥 변환
// https://www.acmicpc.net/problem/29793
// solved.ac: https://solved.ac/search?query=29793
// 시간 제한: 1 초
// 메모리 제한: 1024 MB
// 티어: 🟡 Gold III
// 태그: 다이나믹 프로그래밍, 많은 조건 분기, 문자열, 브루트포스 알고리즘, 애드 혹
// 푼 사람 수: 130
// 평균 시도: 3.34

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

  constexpr char letters[3] = {'S', 'R', 'W'};

  if (H >= 4)
  {
    if (N >= 4)
    {
      cout << -1;
      return 0;
    }
    int kinds = 0;
    vector<bool> used('Z' - 'A' + 1, false);
    for (const char &letter : S)
      if (!used[letter - 'A'])
      {
        used[letter - 'A'] = true;
        ++kinds;
      }

    cout << N - kinds;
    return 0;
  }

  if (H <= 1)
  {
    cout << 0;
    return 0;
  }

  if (H == 2)
  {
    int changes = 0;
    string temp(N, '?');

    temp[0] = S[0];
    for (int i = 1; i < N; ++i)
    {
      if (S[i] != temp[i - 1])
        temp[i] = S[i];
      else
      {
        ++changes;
        char nxt = (i + 1 < N ? S[i + 1] : 0);
        for (const char &letter : letters)
          if (letter != temp[i - 1] && letter != nxt)
          {
            temp[i] = letter;
            break;
          }
      }
    }

    cout << changes;
    return 0;
  }

  int best = N;

  char pattern[6][3] = {
      {'S', 'R', 'W'},
      {'S', 'W', 'R'},
      {'R', 'S', 'W'},
      {'R', 'W', 'S'},
      {'W', 'S', 'R'},
      {'W', 'R', 'S'}};

  for (int p = 0; p < 6; ++p)
  {
    int diff = 0;
    for (int i = 0; i < N; ++i)
      if (S[i] != pattern[p][i % 3])
        ++diff;

    best = min(best, diff);
  }

  cout << best;
  return 0;
}
