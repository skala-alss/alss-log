// 24091 – 알고리즘 수업 - 퀵 정렬 2
// https://www.acmicpc.net/problem/24091
// solved.ac: https://solved.ac/search?query=24091
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver V
// 태그: 구현, 정렬
// 푼 사람 수: 274
// 평균 시도: 2.43

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

  auto partition = [&](int p, int r) -> int
  {
    int pivot = A[r];
    int i = p - 1;
    for (int j = p; j < r; ++j)
    {
      if (A[j] <= pivot)
      {
        swap(A[++i], A[j]);
        --K;
        if (!K)
        {
          for (int &number : A)
            cout << number << ' ';
          return 0;
        }
      }
    }

    if (i + 1 != r)
    {
      swap(A[i + 1], A[r]);
      --K;
      if (!K)
      {
        for (int &number : A)
          cout << number << ' ';
        return 0;
      }
    }

    return i + 1;
  };

  auto quick_sort = [&](auto &&self, int p, int r) -> void
  {
    if (p < r && K)
    {
      int q = partition(p, r);
      self(self, p, q - 1);
      self(self, q + 1, r);
    }
  };

  quick_sort(quick_sort, 0, N - 1);

  if (K)
    cout << -1;
  return 0;
}
