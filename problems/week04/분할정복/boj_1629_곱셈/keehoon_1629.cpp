// 1629 – 곱셈
// https://www.acmicpc.net/problem/1629
// solved.ac: https://solved.ac/search?query=1629
// 시간 제한: 0.5 초 (추가 시간 없음)
// 메모리 제한: 128 MB
// 티어: ⚪ Silver I
// 태그: 분할 정복을 이용한 거듭제곱, 수학
// 푼 사람 수: 34,071
// 평균 시도: 3.56

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

  long long A, B, C;
  cin >> A >> B >> C;

  auto dnq = [&](auto &&self, int exp) -> long long
  {
    if (exp <= 1)
      return (exp ? A : 1) % C;

    long long half = self(self, exp / 2);
    long long power = half * half % C;

    return (exp & 1 ? power * A % C : power);
  };

  cout << dnq(dnq, B);

  return 0;
}
