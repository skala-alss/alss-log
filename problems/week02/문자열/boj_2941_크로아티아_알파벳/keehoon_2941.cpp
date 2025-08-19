// 2941 – 크로아티아 알파벳
// https://www.acmicpc.net/problem/2941
// solved.ac: https://solved.ac/search?query=2941
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver V
// 태그: 구현, 문자열
// 푼 사람 수: 82,171
// 평균 시도: 2.23

#include <iostream>
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

  string S;
  cin >> S;
  int l = S.length();

  for (int i = l - 1; i >= 0; --i)
  {
    if (S[i] == '=')
    {
      if (0 < i)
        if (S[i - 1] == 'c' || S[i - 1] == 's')
          --l;
        else if (S[i - 1] == 'z')
        {
          --l;
          if (1 < i && S[i - 2] == 'd')
            --l;
        }
    }
    else if (S[i] == '-')
    {
      if (0 < i && (S[i - 1] == 'c' || S[i - 1] == 'd'))
        --l;
    }
    else if (S[i] == 'j')
    {
      if (0 < i && (S[i - 1] == 'l' || S[i - 1] == 'n'))
        --l;
    }
  }
  cout << l;
  return 0;
}
