// 24315 – 알고리즘 수업 - 점근적 표기 3
// https://www.acmicpc.net/problem/24315
// solved.ac: https://solved.ac/search?query=24315
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver IV
// 태그: 수학
// 푼 사람 수: 276
// 평균 시도: 1.32

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

  int a1, a0, c1, c2, n0;
  cin >> a1 >> a0 >> c1 >> c2 >> n0;

  /*
     --- Θ(세타) 표기 정의 ---
     f(n) ∈ Θ(g(n))  ⇔  ∃ c1 > 0, c2 > 0, n0 > 0 s.t.
       c1 * g(n) ≤ f(n) ≤ c2 * g(n)   for all n ≥ n0

     이번 문제:
       f(n) = a1 * n + a0,   g(n) = n
       ⇒  c1 * n ≤ a1 * n + a0 ≤ c2 * n   (모든 n ≥ n0)

     이를 좌우로 분리하여 각각 정리하면,

     [하한(Ω) 조건]  a1 * n + a0 ≥ c1 * n
       ⇔ (a1 - c1) * n + a0 ≥ 0
       충분조건:
         (i)  a1 ≥ c1        // 기울기(계수) 비교
         (ii) (a1 - c1) * n0 + a0 ≥ 0   // 시작점 n0에서부터 성립 확인

     [상한(O) 조건]   a1 * n + a0 ≤ c2 * n
       ⇔ (a1 - c2) * n + a0 ≤ 0
       충분조건:
         (i)  a1 ≤ c2
         (ii) (a1 - c2) * n0 + a0 ≤ 0

     결국 Θ(n) 판정은 아래 네 조건을 모두 만족하는지로 귀결된다:
       1) a1 ≥ c1
       2) (a1 - c1) * n0 + a0 ≥ 0
       3) a1 ≤ c2
       4) (a1 - c2) * n0 + a0 ≤ 0

     ※ 직관:
       - a1은 f(n)의 기울기, c1·c2는 비교 직선의 기울기.
       - n이 충분히 클 때 f(n)이 c1*n과 c2*n 사이에 ‘끼어 있다’면 Θ(n).
       - n0에서의 상수항 a0 영향까지 고려하려면 (ii) 조건들이 필요.
   */

  cout << (a1 >= c1 && (a1 - c1) * n0 + a0 >= 0 && a1 <= c2 && (a1 - c2) * n0 + a0 <= 0 ? 1 : 0);
  return 0;
}
