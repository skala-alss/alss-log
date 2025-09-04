// 23969 – 알고리즘 수업 - 버블 정렬 2
// https://www.acmicpc.net/problem/23969
// solved.ac: https://solved.ac/search?query=23969
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟫 Bronze I
// 태그: 구현, 시뮬레이션, 정렬
// 푼 사람 수: 820
// 평균 시도: 1.91

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

  for (int last = N - 1; last > 0; --last)
    for (int i = 0; i < last; ++i)
    {
      if (A[i] > A[i + 1])
      {
        swap(A[i], A[i + 1]);
        --K;
        if (!K)
        {
          for (int &number : A)
            cout << number << ' ';
          return 0;
        }
      }
    }

  cout << -1;
  return 0;
}
