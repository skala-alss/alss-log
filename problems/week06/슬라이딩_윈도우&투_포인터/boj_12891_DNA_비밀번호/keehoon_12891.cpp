// 12891 – DNA 비밀번호
// https://www.acmicpc.net/problem/12891
// solved.ac: https://solved.ac/search?query=12891
// 시간 제한: 2 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver II
// 태그: 문자열, 슬라이딩 윈도우
// 푼 사람 수: 9,445
// 평균 시도: 2.79

#include <iostream>
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

  int S, P, A, C, G, T;
  string s;
  cin >> S >> P;
  cin >> s >> A >> C >> G >> T;

  unordered_map<char, int> condition = {{'A', A},
                                        {'C', C},
                                        {'G', G},
                                        {'T', T}};
  unordered_map<char, int> substring;
  int cnt = 0;
  for (int i = 0; i < S; ++i)
  {
    ++substring[s[i]];
    i >= P && --substring[s[i - P]];

    if (i >= P - 1)
    {
      bool ok = true;
      for (auto kv : condition)
        if (kv.second > substring[kv.first])
          ok = false;

      if (ok)
        ++cnt;
    }
  }

  cout << cnt;

  return 0;
}
