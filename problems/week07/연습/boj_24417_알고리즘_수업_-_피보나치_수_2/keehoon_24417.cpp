// 24417 – 알고리즘 수업 - 피보나치 수 2
// https://www.acmicpc.net/problem/24417
// solved.ac: https://solved.ac/search?query=24417
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver IV
// 태그: 다이나믹 프로그래밍, 수학
// 푼 사람 수: 898
// 평균 시도: 3.14

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

  int n;
  cin >> n;
  long long t1 = 1, t2 = 1, t3;
  for (int i = 3; i <= n; ++i)
  {
    t3 = (t1 + t2) % 1'000'000'007;
    swap(t1, t2);
    swap(t2, t3);
  }

  cout << t2 << ' ' << n - 2;

  return 0;
}
