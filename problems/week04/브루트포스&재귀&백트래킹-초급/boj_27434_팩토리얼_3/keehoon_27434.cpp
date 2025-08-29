// 27434 – 팩토리얼 3
// https://www.acmicpc.net/problem/27434
// solved.ac: https://solved.ac/search?query=27434
// 시간 제한: 4 초 (추가 시간 없음)
// 메모리 제한: 1024 MB
// 티어: 🟫 Bronze V
// 태그: 사칙연산, 수학, 임의 정밀도 / 큰 수 연산
// 푼 사람 수: 4,356
// 평균 시도: 2.17
//
// ──────────────────────────────────────────────────────────────────────────────
// 이 파일은 "큰 정수(Big Integer)"와 "분할정복 곱셈(Product Tree) + Karatsuba"를
// 이용해 N! (0 ≤ N ≤ 100,000)을 출력하는 프로그램입니다.
//
// 핵심 아이디어 요약
// 1) 일반 정수형(long long, __int128)로는 100000! 를 담을 수 없어 "직접 만든 큰 정수"가 필요.
// 2) 1부터 N까지 순서대로 곱하면 너무 느리므로, [L..R]을 절반으로 쪼개
//    P(L,R)=P(L,M)*P(M+1,R) 형태로 곱을 결합하는 "Product Tree(분할정복)"를 사용.
// 3) 큰 정수 × 큰 정수 곱은 자릿수가 커질수록 O(n^2) 방식이 느려지므로,
//    자릿수가 충분히 커지면 Karatsuba(복잡도 약 O(n^1.585))로 전환해 가속.
//
// 구현 디테일 요약
// - 큰 정수는 10^9(9자리)를 한 덩어리(limb)로 하는 '리틀 엔디언' 벡터로 저장.
//   예: 1234567890123456789  ⇒  [23456789, 123456789, 1]  (a[0]가 하위 9자리)
// - 작은 정수(64비트)와의 곱은 자리올림(carry)만 잘 처리하면 빠르게 가능.
// - 큰 정수 × 큰 정수 곱은 크기에 따라
//     * 작으면: 학교식 O(n^2) (mul_simple)
//     * 크면: 카라추바(Karatsuba)로 재귀 곱 (karatsuba)
// - Product Tree의 리프(길이가 충분히 작을 때)는 Big × small 반복으로 처리하여
//   Big × Big 호출을 최소화.
//
// 주의 사항
// - __uint128_t: GCC/Clang 확장 정수형. BOJ(g++17) 환경에서는 사용 가능.
//   (MSVC에선 지원 X)
//
// ──────────────────────────────────────────────────────────────────────────────

#include <iostream>
#include <cstdint>
#include <iomanip>
#include <vector>
#if defined(_WIN32)
#include <io.h>
#include <cstdio>
#else
#include <unistd.h>
#include <cstdio>
#endif

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Big: "직접 만든 큰 정수" 자료형
//  - BASE = 10^9: 9자리씩 끊어서 저장 (uint32_t에 안전하게 들어감)
//  - a 벡터: little-endian 저장 (a[0]가 가장 하위 9자리)
//  - 예:  1234567890123  ⇒  a = [ 120123, 456789, 1 ]  (각 원소는 0..BASE-1)
//  - 장점: 출력 시 앞쪽 덩어리만 0패딩(9자리) 맞추면 매우 편함
// ──────────────────────────────────────────────────────────────────────────────
struct Big
{
  static const uint32_t BASE = 1000000000; // 10^9 (9자리)
  // a[0] = 가장 하위 9자리, a.back() = 가장 상위 9자리
  vector<uint32_t> a;

  // 기본 생성자: 0을 의미 (벡터 비어있음)
  Big() {}

  // 64비트 정수로부터 생성 (작은 값을 Big으로 만들 때 사용)
  Big(uint64_t v)
  {
    if (v == 0)
      return;
    while (v)
    {
      // v를 10^9로 나눈 나머지를 하위 limb로 push
      a.push_back((uint32_t)(v % BASE));
      v /= BASE;
    }
  }

  // 현재 값이 0인지? (벡터가 비어 있으면 0으로 간주)
  bool isZero() const { return a.empty(); }

  // 상위에 쌓인 0 limb 제거 (연산 후 길이 정리)
  void trim()
  {
    while (!a.empty() && a.back() == 0)
      a.pop_back();
  }

  // ──────────────────────────────────────────────────────────────────────────
  // mul_small: "Big × 작은 정수(uint64_t)" 곱
  // - 매 자리마다 a[i]*m + carry 를 계산하고,
  //   현재 자리 = (그 결과 % BASE), carry = (그 결과 / BASE) 로 갱신
  // - 마지막에 carry가 남아 있으면 계속 limb 추가
  // - 작은 정수와의 곱은 Big×Big보다 훨씬 저렴해서, 리프 구간에서 적극 사용
  // ──────────────────────────────────────────────────────────────────────────
  void mul_small(uint64_t m)
  {
    if (isZero() || m == 1)
      return; // 0×m=0,  x×1=x 는 변화 없음
    if (m == 0)
    {
      a.clear(); // 모든 값이 0이 됨
      return;
    }

    // __uint128_t: 64비트×64비트 + carry 를 안전하게 담기 위해 사용
    __uint128_t carry = 0;
    for (size_t i = 0; i < a.size(); ++i)
    {
      // cur = 현재 limb × m + carry
      __uint128_t cur = (__uint128_t)a[i] * m + carry;

      // 하위 9자리는 이 limb로
      a[i] = (uint32_t)(cur % BASE);
      // 나머지는 다음 자리로 carry
      carry = cur / BASE;
    }
    // 마지막 carry가 남아있다면 limb를 추가하며 분해
    while (carry)
    {
      a.push_back((uint32_t)(carry % BASE));
      carry /= BASE;
    }
  }

  // ──────────────────────────────────────────────────────────────────────────
  // add: 두 Big을 더해 새로운 Big을 반환 (c = x + y)
  // - 같은 자리끼리 더하고 carry 전파
  // - 길이가 다른 경우, 없는 자리는 0으로 간주
  // ──────────────────────────────────────────────────────────────────────────
  static Big add(const Big &x, const Big &y)
  {
    Big c;
    const size_t n = max(x.a.size(), y.a.size());
    c.a.resize(n);
    uint64_t carry = 0;

    for (size_t i = 0; i < n; ++i)
    {
      uint64_t s = carry;
      if (i < x.a.size())
        s += x.a[i];
      if (i < y.a.size())
        s += y.a[i];

      c.a[i] = (uint32_t)(s % BASE);
      carry = s / BASE;
    }
    if (carry)
      c.a.push_back((uint32_t)carry);
    return c;
  }

  // ──────────────────────────────────────────────────────────────────────────
  // subInPlace: x -= y  (단, x >= y 라고 가정)
  // - Karatsuba 내부에서 (x0+x1)*(y0+y1) - z0 - z2 같은 계산에 사용
  // - 음수가 나오면 BASE를 더해주고 carry=-1 로 다음 자리에서 1을 빌림
  // ──────────────────────────────────────────────────────────────────────────
  static void subInPlace(Big &x, const Big &y)
  {
    int64_t carry = 0;
    for (size_t i = 0; i < x.a.size(); ++i)
    {
      int64_t s = (int64_t)x.a[i] - (i < y.a.size() ? y.a[i] : 0) + carry;

      if (s < 0)
      {
        // 현재 자리가 음수라면 1 BASE를 빌려서 더해줌
        s += BASE;
        carry = -1; // 다음 자리에서 1을 더 빼야 함을 표시
      }
      else
      {
        carry = 0;
      }
      x.a[i] = (uint32_t)s;
    }
    x.trim(); // 상위 0 제거
  }

  // ──────────────────────────────────────────────────────────────────────────
  // addShifted: z += (src << (shift limbs))
  // - "<< (shift limbs)"는 10^9 단위 limb 기준으로의 자리 이동 (9*shift 자리 이동)
  // - Karatsuba 결과 조립: z2 << (2*k), z1 << k, z0 를 더할 때 사용
  // ──────────────────────────────────────────────────────────────────────────
  static void addShifted(Big &z, const Big &src, size_t shift)
  {
    if (src.a.empty())
      return;

    // z의 길이가 부족하면 확장 (뒤쪽에 0을 채움)
    if (z.a.size() < src.a.size() + shift)
      z.a.resize(src.a.size() + shift, 0);

    uint64_t carry = 0;
    for (size_t i = 0; i < src.a.size(); ++i)
    {
      // 대상 위치는 i+shift (shift만큼 왼쪽 이동)
      uint64_t s = (uint64_t)z.a[i + shift] + src.a[i] + carry;
      z.a[i + shift] = (uint32_t)(s % BASE);
      carry = s / BASE;
    }
    // 남은 carry 전파
    size_t i = src.a.size() + shift;
    while (carry)
    {
      if (i >= z.a.size())
        z.a.push_back(0);
      uint64_t s = (uint64_t)z.a[i] + carry;
      z.a[i] = (uint32_t)(s % BASE);
      carry = s / BASE;
      ++i;
    }
  }

  // ──────────────────────────────────────────────────────────────────────────
  // mul_simple: 학교식 O(n^2) 곱셈
  // - 작은 크기에서는 Karatsuba보다 상수가 작아 더 빠름
  // - (x.a.size() * y.a.size()) 회선으로 단순 곱 + carry 전파
  // ──────────────────────────────────────────────────────────────────────────
  static Big mul_simple(const Big &x, const Big &y)
  {
    if (x.isZero() || y.isZero())
      return Big();
    Big z;
    z.a.assign(x.a.size() + y.a.size(), 0);

    for (size_t i = 0; i < x.a.size(); ++i)
    {
      __uint128_t carry = 0; // 64비트 곱 결과 합에도 안전한 128비트
      uint64_t xi = x.a[i];  // 현재 자리의 값 (0..BASE-1)

      // j < y.a.size() || carry: carry가 남아있는 동안에도 수행
      for (size_t j = 0; j < y.a.size() || carry; ++j)
      {
        // z.a[i+j] 기존값 + xi * y[j] + carry
        __uint128_t cur = z.a[i + j] + carry + (__uint128_t)xi * (j < y.a.size() ? y.a[j] : 0);

        z.a[i + j] = (uint32_t)(cur % BASE); // 하위 9자리 저장
        carry = cur / BASE;                  // 나머지는 다음 자리로
      }
    }
    z.trim();
    return z;
  }

  // ──────────────────────────────────────────────────────────────────────────
  // karatsuba: Karatsuba 곱셈 (분할정복 기반)
  //
  // 수식 개요:
  //   x = x1 * B^k + x0
  //   y = y1 * B^k + y0   (B = BASE = 10^9, k = 절반 길이)
  //
  //   x*y = z2 * B^(2k) + z1 * B^k + z0
  //   where
  //     z0 = x0*y0
  //     z2 = x1*y1
  //     z1 = (x0+x1)*(y0+y1) - z0 - z2
  //
  // 길이가 작으면 mul_simple으로 내려가고,
  // 충분히 크면 위 공식을 이용해 재귀적으로 빠르게 계산.
  // ──────────────────────────────────────────────────────────────────────────
  static Big karatsuba(const Big &x, const Big &y)
  {
    size_t n = max(x.a.size(), y.a.size());

    // 임계치: 실측/환경에 따라 32~128 사이에서 조정
    // - 너무 작으면 재귀/할당 오버헤드로 느려짐
    // - 너무 크면 O(n^2) 구간이 길어져 느려짐
    if (n < 64)
      return mul_simple(x, y);

    size_t k = n / 2;

    // x = x1 * BASE^k + x0   (y도 동일)
    Big x0, x1, y0, y1;
    x0.a.assign(x.a.begin(), x.a.begin() + min(x.a.size(), k)); // 하위 절반
    x1.a.assign(x.a.begin() + min(x.a.size(), k), x.a.end());   // 상위 절반
    y0.a.assign(y.a.begin(), y.a.begin() + min(y.a.size(), k));
    y1.a.assign(y.a.begin() + min(y.a.size(), k), y.a.end());
    x0.trim();
    x1.trim();
    y0.trim();
    y1.trim();

    // z0 = x0*y0
    Big z0 = karatsuba(x0, y0);
    // z2 = x1*y1
    Big z2 = karatsuba(x1, y1);

    // z1 = (x0+x1)*(y0+y1) - z0 - z2
    Big sx = add(x0, x1);
    Big sy = add(y0, y1);
    Big z1 = karatsuba(sx, sy);
    subInPlace(z1, z0);
    subInPlace(z1, z2);

    // 결과 조립: res = z2 << (2*k) + z1 << k + z0
    Big res;
    // (초기 크기를 어느 정도 확보해둠. 부족하면 addShifted가 알아서 늘림)
    res.a.assign(z2.a.size() + 2 * k, 0);
    addShifted(res, z2, 2 * k);
    addShifted(res, z1, k);
    addShifted(res, z0, 0);
    res.trim();
    return res;
  }

  // 연산자 오버로드: x * y
  friend Big operator*(const Big &x, const Big &y)
  {
    if (x.isZero() || y.isZero())
      return Big();
    return karatsuba(x, y);
  }
};

// ──────────────────────────────────────────────────────────────────────────────
// rangeProdSmall: [L..R] 구간의 곱을 "Big × 작은 정수"만으로 계산
// - 리프(작은 길이)에서 사용하여 Big×Big 호출을 줄이는 게 목적
// - 각 단계: res *= v; (v는 64비트 정수)
// - 복잡도: O((R-L+1) × 현재 자릿수)
//   (하지만 리프 길이를 작게 유지하므로 전체 성능엔 이득)
// ──────────────────────────────────────────────────────────────────────────────
static Big rangeProdSmall(uint64_t L, uint64_t R)
{
  Big res(1);
  for (uint64_t v = L; v <= R; ++v)
    res.mul_small(v);
  return res;
}

// ──────────────────────────────────────────────────────────────────────────────
// rangeProd: Product Tree (분할정복)로 [L..R] 구간 곱 계산
// - 길이가 충분히 크면 반으로 쪼개 재귀적으로 계산하고, 마지막에 두 덩어리를 Big×Big으로 곱
// - 길이가 작으면 rangeProdSmall로 내려가 Big×small 반복으로 처리
//
// 장점:
// - 균형 트리로 곱을 결합하면,
//   * 각 단계의 피연산자 크기가 비슷해 Karatsuba가 이점을 더 크게 가짐
//   * Big×Big 호출 횟수를 필요 최소화
// - 단순 1..N 순차 곱(누적)보다 캐시/상수면에서도 유리
// ──────────────────────────────────────────────────────────────────────────────
static Big rangeProd(uint64_t L, uint64_t R)
{
  if (L > R)
    return Big(1); // 공집합 곱은 항등원 1
  uint64_t len = R - L + 1;

  // 리프 길이 임계치: 32~128 사이가 보통 무난. 여기서는 64.
  // - 작을수록 Big×small 위주로 자주 내려가고,
  // - 클수록 Big×Big 호출이 늘어남. 실측으로 조정 가능.
  if (len <= 64)
    return rangeProdSmall(L, R);

  uint64_t M = (L + R) >> 1;       // 중간 지점
  Big left = rangeProd(L, M);      // 왼쪽 구간 곱
  Big right = rangeProd(M + 1, R); // 오른쪽 구간 곱
  return left * right;             // 두 덩어리를 Big×Big으로 결합 (Karatsuba 내부 사용)
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // ───────────────────────────────────────────────────────────────────────────
  // [편의 기능] 터미널에서 실행하면 input.txt를 stdin으로 사용
  // - BOJ 채점 환경(파이프/리다이렉트)에서는 isatty(...)가 false이므로 영향 없음
  // - 로컬 디버깅시에만 동작
  // ───────────────────────────────────────────────────────────────────────────
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
  if (!(cin >> N))
    return 0;
  if (N <= 1) // 0! = 1, 1! = 1
  {
    cout << 1 << '\n';
    return 0;
  }

  // 2 * 3 * ... * N 을 Product Tree로 계산
  Big ans = rangeProd(2, (uint64_t)N);

  // ───────────────────────────────────────────────────────────────────────────
  // 출력: 10^9(9자리) 단위로 저장되어 있으므로
  // - 가장 상위 limb는 그대로 출력
  // - 그보다 낮은 limb들은 항상 9자리를 채워서(0 패딩) 출력
  //   예: [12][000000345][000001234]  ⇒  12 000000345 000001234
  // ───────────────────────────────────────────────────────────────────────────
  if (ans.isZero())
  {
    // N≥2이면 0이 될 일은 사실상 없음(여기선 안전성 차원)
    cout << 0 << '\n';
    return 0;
  }

  auto &v = ans.a;
  int i = (int)v.size() - 1;

  // 최상위 limb (맨 앞)은 그대로 출력 (앞에 0을 채우면 안 됨)
  cout << v[i];

  // 나머지 limb는 9자리 고정 폭 + '0'으로 왼쪽 채움
  // (setfill은 스트림에 상태로 남으니 루프 바깥에서 한 번만 해도 되지만,
  //  여기서는 각 줄에서 명시적으로 지정해 가독성을 유지)
  for (i = i - 1; i >= 0; --i)
  {
    cout << setw(9) << setfill('0') << v[i];
  }
  cout << '\n';
  return 0;
}
