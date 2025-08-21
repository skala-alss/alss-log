// 11720 – 숫자의 합
// https://www.acmicpc.net/problem/11720
// solved.ac: https://solved.ac/search?query=11720
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: 🟫 Bronze IV
// 태그: 구현, 문자열, 수학
// 푼 사람 수: 143,213
// 평균 시도: 1.78

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
  string number;
  cin >> N >> number;
  int sum = 0;
  for (char digit : number)
    sum += digit - '0';
  cout << sum;
  return 0;
}
