// 24263 – 알고리즘 수업 - 알고리즘의 수행 시간 2
// https://www.acmicpc.net/problem/24263
// solved.ac: https://solved.ac/search?query=24263
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟫 Bronze IV
// 태그: 구현, 시뮬레이션
// 푼 사람 수: 20,002
// 평균 시도: 1.25

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

  int n;
  cin >> n;
  cout << n << '\n'
       << 1;
  return 0;
}
