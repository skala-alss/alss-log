// 24370 – 알고리즘 수업 - 점근적 표기 6
// https://www.acmicpc.net/problem/24370
// solved.ac: https://solved.ac/search?query=24370
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver I
// 태그: 많은 조건 분기, 수학
// 푼 사람 수: 95
// 평균 시도: 3.49

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

  float a2, a1, a0, c1, c2, n0;
  cin >> a2 >> a1 >> a0 >> c1 >> c2 >> n0;

  float A1 = a2 - c1, A2 = a2 - c2, B = a1, C = a0;

  /**
   * 문제 설명:
   *   다항식 f(n) = a2 * n^2 + a1 * n + a0 가 주어진다.
   *   그리고 두 비교 함수 g1(n) = c1 * n^2, g2(n) = c2 * n^2 가 있다.
   *   조건: ∀ n ≥ n0 에 대하여 g1(n) ≤ f(n) ≤ g2(n) 인지 판정해야 한다.
   *
   * 수식 변환:
   *   1. g1(n) ≤ f(n) ⇔ (a2 - c1) * n^2 + a1 * n + a0 ≥ 0 → h1(n) ≥ 0
   *   2. f(n) ≤ g2(n) ⇔ (a2 - c2) * n^2 + a1 * n + a0 ≤ 0 → h2(n) ≤ 0
   *
   *   즉, 두 조건을 동시에 만족하는지 검사해야 한다.
   *
   * 알고리즘 핵심:
   *   - h1(n) = A1 n^2 + B n + C ≥ 0, h2(n) = A2 n^2 + B n + C ≤ 0.
   *   - h2(n) ≤ 0 조건은 -h2(n) ≥ 0 으로 바꿔서 h1과 동일한 판정 구조로 통일.
   *   - 따라서 `check(a, b, c)` 함수는 a n^2 + b n + c ≥ 0 여부를 ∀ n ≥ n0 에 대해 판정한다.
   *
   * check(a, b, c) 로직:
   *   1. a < 0:
   *      - 아래로 열린 포물선 → n→∞에서 -∞ → 절대 성립 불가 → false.
   *
   *   2. a == 0 (선형):
   *      - 직선 b n + c.
   *      - b < 0: n→∞에서 -∞ → 불가능.
   *      - b ≥ 0: 최소값은 n0에서 달성. b*n0 + c ≥ 0 이어야 성립.
   *
   *   3. a > 0 (위로 열린 포물선):
   *      - [n0, ∞) 구간에서 최소값은 꼭짓점 x = -b/(2a) 또는 n0 중 큰 쪽에서 달성.
   *      - min_val = max(x, n0).
   *      - 해당 지점의 함수값 ≥ 0 이면 조건 충족.
   *
   * 전체 판정:
   *   - check(A1, B, C): 하한 g1(n) ≤ f(n).
   *   - check(-A2, -B, -C): 상한 f(n) ≤ g2(n)을 -h2(n) ≥ 0 꼴로 변환.
   *   - 두 조건을 모두 만족하면 "1", 아니면 "0".
   */

  auto check = [&](float a, float b, float c) -> bool
  {
    if (a < 0)
      return false;

    if (a == 0)
    {
      if (b < 0)
        return false;
      return b * n0 + c >= 0;
    }

    float x = -b / (2 * a);
    float min_val = max(x, n0);
    float val = a * min_val * min_val + b * min_val + c;

    return val >= 0;
  };

  cout << (check(A1, B, C) && check(-A2, -B, -C) ? 1 : 0);

  return 0;
}
