// 24368 – 알고리즘 수업 - 점근적 표기 4
// https://www.acmicpc.net/problem/24368
// solved.ac: https://solved.ac/search?query=24368
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver I
// 태그: 많은 조건 분기, 수학
// 푼 사람 수: 151
// 평균 시도: 7.50

#include <cmath>
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

  int a2, a1, a0, c, n0;
  cin >> a2 >> a1 >> a0 >> c >> n0;

  int A = a2 - c, B = a1, C = a0;

  // f(n) = a2*n^2 + a1*n + a0, g(n) = n^2
  // 문제: ∀ 실수 n ≥ n0 에 대해 f(n) ≤ c*g(n) 인지 판정
  // ⇔ F(n) = (a2 - c)*n^2 + a1*n + a0 ≤ 0 (∀ n ≥ n0)

  // 핵심 아이디어:
  // - A = a2 - c
  // - A > 0: 위로 볼록 → n→∞에서 F(n) → +∞ → 절대 성립 불가
  // - A = 0: 선형 Bn + C, 단조 성질에 따라 판정
  // - A < 0: 아래로 볼록 → 최대는 꼭짓점 또는 n0에서 발생
  //           ∀ 실수 n≥n0 에서 최대값이 0 이하인지 확인

  // F(n) = A n^2 + B n + C
  auto val = [&](float n) -> float
  {
    return A * n * n + B * n + C;
  };

  // --- Case 1: A > 0 ---
  // 위로 볼록. n 커지면 F(n) 양의 무한대로 발산 → 불가능
  if (A > 0)
  {
    cout << 0;
    return 0;
  }

  // --- Case 2: A = 0 ---
  // 선형식 F(n) = Bn + C
  // · B > 0 → 증가 → 언젠가 양수 → 불가능
  // · B ≤ 0 → 감소/상수 → n0에서만 확인
  if (A == 0)
  {
    if (B > 0)
    {
      cout << 0;
      return 0;
    }
    cout << ((B * n0 + C) <= 0 ? 1 : 0);
    return 0;
  }

  // --- Case 3: A < 0 ---
  // 아래로 볼록. 최대는 꼭짓점 x* 또는 n0에서 발생
  // 꼭짓점 좌표 x* = -B / (2A)
  float x = -float(B) / (2 * float(A));

  // n0보다 오른쪽이면 x*에서 최대, 왼쪽이면 n0에서 최대
  float max_val = max(float(n0), x);

  // 최대값이 0 이하이면 O(n^2) 정의 만족
  cout << (val(max_val) <= 0 ? 1 : 0);

  return 0;
}
