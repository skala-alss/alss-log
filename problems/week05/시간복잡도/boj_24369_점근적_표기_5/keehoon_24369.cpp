// 24369 – 알고리즘 수업 - 점근적 표기 5
// https://www.acmicpc.net/problem/24369
// solved.ac: https://solved.ac/search?query=24369
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver I
// 태그: 많은 조건 분기, 수학
// 푼 사람 수: 112
// 평균 시도: 2.58

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

  float a2, a1, a0, c, n0;
  cin >> a2 >> a1 >> a0 >> c >> n0;

  float A = a2 - c, B = a1, C = a0;

  /**
   * 문제 설명:
   *   함수 f(n) = a2 * n^2 + a1 * n + a0 가 주어진다.
   *   또한 g(n) = c * n^2 가 주어질 때, f(n) ≤ g(n) ∀ n ≥ n0 인지 판정해야 한다.
   *
   * 핵심 아이디어:
   *   f(n) ≤ g(n) ⇔ (a2 - c) * n^2 + a1 * n + a0 ≤ 0
   *   따라서 새로운 다항식 h(n) = A * n^2 + B * n + C 를 정의한다 (A = a2 - c, B = a1, C = a0).
   *   문제는 h(n) ≤ 0 ∀ n ≥ n0 를 만족하는지 확인하는 것으로 바뀐다.
   *
   * 판정 절차:
   *   1. A < 0 인 경우:
   *      - 음수 계수이므로 n이 커질수록 음의 무한대로 발산한다.
   *      - 따라서 n0 이상의 모든 값에서 결국 조건을 만족하지 않으므로 "0" 출력.
   *
   *   2. A == 0 인 경우 (선형 함수):
   *      - h(n) = Bn + C
   *      - 만약 B < 0 이면, n 증가에 따라 음의 무한대로 발산 → 항상 조건 만족 불가 → "0".
   *      - 그렇지 않다면, h(n0) ≥ 0 여부만 판정.
   *
   *   3. A > 0 인 경우 (이차함수 위로 열린 포물선):
   *      - 최소값은 꼭짓점 x = -B / (2A) 에서 발생.
   *      - n ≥ n0 범위에서 최소값이 발생하는 지점은 max(x, n0).
   *      - h(min_val) ≥ 0 이면 조건 만족, 아니면 불만족.
   */

  auto val = [&](float n) -> float
  {
    return A * n * n + B * n + C;
  };

  if (A < 0)
  {
    cout << 0;
    return 0;
  }

  if (A == 0)
  {
    if (B < 0)
    {
      cout << 0;
      return 0;
    }
    cout << (B * n0 + C >= 0 ? 1 : 0);
    return 0;
  }

  float x = -B / (2 * A);
  float min_val = max(x, n0);

  cout << (val(min_val) >= 0 ? 1 : 0);

  return 0;
}
