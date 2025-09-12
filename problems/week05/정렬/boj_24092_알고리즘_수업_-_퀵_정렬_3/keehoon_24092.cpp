// 24092 – 알고리즘 수업 - 퀵 정렬 3
// https://www.acmicpc.net/problem/24092
// solved.ac: https://solved.ac/search?query=24092
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver I
// 태그: 구현, 애드 혹, 정렬
// 푼 사람 수: 166
// 평균 시도: 5.37

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

  int N;
  cin >> N;
  vector<int> A(N);
  for (int &number : A)
    cin >> number;

  vector<int> B(N);
  for (int &number : B)
    cin >> number;

  int diff = 0;
  for (int i = 0; i < N; ++i)
    if (A[i] != B[i])
      ++diff;

  if (!diff)
  {
    cout << 1;
    exit(0);
  }

  auto apply_swap = [&](int x, int y) -> void
  {
    int before = (A[x] != B[x]) + (A[y] != B[y]);
    swap(A[x], A[y]);
    int after = (A[x] != B[x]) + (A[y] != B[y]);
    diff += after - before;
    if (!diff)
    {
      cout << 1;
      exit(0);
    }
  };

  auto partition = [&](int p, int r) -> int
  {
    int pivot = A[r];
    int i = p - 1;
    for (int j = p; j < r; ++j)
      if (A[j] <= pivot)
        apply_swap(++i, j);
    if (i + 1 != r)
      apply_swap(i + 1, r);

    return i + 1;
  };

  auto quick_sort = [&](auto &&self, int p, int r) -> void
  {
    if (p < r)
    {
      int q = partition(p, r);
      self(self, p, q - 1);
      self(self, q + 1, r);
    }
  };

  quick_sort(quick_sort, 0, N - 1);

  cout << 0;

  return 0;
}
