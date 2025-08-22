// 2675 – 문자열 반복
// https://www.acmicpc.net/problem/2675
// solved.ac: https://solved.ac/search?query=2675
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: 🟫 Bronze II
// 태그: 구현, 문자열
// 푼 사람 수: 121,629
// 평균 시도: 1.99

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

  int T;
  cin >> T;
  while (T--)
  {
    int R;
    string S;
    cin >> R >> S;

    for (char l : S)
      for (int i = 1; i <= R; ++i)
        cout << l;
    cout << '\n';
  }
  return 0;
}
