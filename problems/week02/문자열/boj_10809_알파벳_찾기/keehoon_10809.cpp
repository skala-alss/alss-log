// 10809 – 알파벳 찾기
// https://www.acmicpc.net/problem/10809
// solved.ac: https://solved.ac/search?query=10809
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: 🟫 Bronze II
// 태그: 구현, 문자열
// 푼 사람 수: 121,319
// 평균 시도: 1.86

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

  string S;
  cin >> S;

  vector<int> locations(26, -1);

  for (int i = S.length() - 1; i >= 0; --i)
    locations[S[i] - 'a'] = i;

  for (int location : locations)
    cout << location << ' ';
  return 0;
}
