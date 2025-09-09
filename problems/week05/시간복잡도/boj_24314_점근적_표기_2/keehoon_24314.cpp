// 24314 – 알고리즘 수업 - 점근적 표기 2
// https://www.acmicpc.net/problem/24314
// solved.ac: https://solved.ac/search?query=24314
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver V
// 태그: 수학
// 푼 사람 수: 337
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

  int a1, a0, c, n0;
  cin >> a1 >> a0 >> c >> n0;

  /*
     --- Ω 표기 정의 ---
     f(n) = a1 * n + a0
     g(n) = n

     f(n) ∈ Ω(g(n)) 이려면:
       ∃ c > 0, n0 > 0 such that
       f(n) >= c * g(n)  for all n >= n0

     즉, 이번 문제에서는:
       a1 * n + a0 >= c * n   (n >= n0)

     --- 부등식 정리 ---
       (a1 - c) * n + a0 >= 0

     조건이 항상 성립하려면:

     1) 기울기 비교:
        a1 >= c
        (a1이 c보다 작으면, n이 커질수록 왼쪽이 무한히 작아져서 성립 불가)

     2) 시작점(n0) 확인:
        (a1 - c) * n0 + a0 >= 0
        (n이 n0 이상일 때도 성립해야 하므로, n0에서부터 부등식 검증 필요)

     두 조건을 모두 만족해야 f(n)이 Ω(n)이다.
   */

  cout << (a1 >= c && (a1 - c) * n0 + a0 >= 0 ? 1 : 0);
  return 0;
}
