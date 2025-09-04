// 24051 – 알고리즘 수업 - 삽입 정렬 1
// https://www.acmicpc.net/problem/24051
// solved.ac: https://solved.ac/search?query=24051
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟫 Bronze I
// 태그: 구현, 시뮬레이션, 정렬
// 푼 사람 수: 1,003
// 평균 시도: 2.59

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

  int N, K;
  cin >> N >> K;
  vector<int> A(N);
  for (int &number : A)
    cin >> number;

  auto write = [&](int idx, int val) -> bool
  {
    A[idx] = val;
    return --K;
  };

  for (int i = 1; i < N; ++i)
  {
    int loc = i - 1;
    int target = A[i];

    while (0 <= loc and target < A[loc])
    {
      if (!write(loc + 1, A[loc]))
      {
        cout << A[loc + 1];
        return 0;
      }
      --loc;
    }

    if (loc + 1 != i)
    {
      if (!write(loc + 1, target))
      {
        cout << target;
        return 0;
      }
      --loc;
    }
  }

  cout << -1;
  return 0;
}
