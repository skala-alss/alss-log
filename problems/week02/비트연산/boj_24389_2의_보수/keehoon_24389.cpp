// 24389 – 2의 보수
// https://www.acmicpc.net/problem/24389
// solved.ac: https://solved.ac/search?query=24389
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟫 Bronze I
// 태그: 비트마스킹, 수학
// 푼 사람 수: 1,073
// 평균 시도: 1.35

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

  int N;
  cin >> N;

  // int complement_of_two = N ^ ~N + 1;
  // int complement_of_two = N ^ ((1 << 32) - N);
  int complement_of_two = N ^ -N;

  int count = 0;
  while (complement_of_two)
  {
    complement_of_two &= complement_of_two - 1;
    ++count;
  }

  cout << count;
}
