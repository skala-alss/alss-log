// 24060 – 알고리즘 수업 - 병합 정렬 1
// https://www.acmicpc.net/problem/24060
// solved.ac: https://solved.ac/search?query=24060
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver III
// 태그: 구현, 재귀, 정렬
// 푼 사람 수: 9,136
// 평균 시도: 2.10

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

  auto merge = [&](int p, int q, int r) -> void
  {
    vector<int> tmp;
    tmp.reserve(r - p + 1);

    int i = p, j = q + 1;
    while (i <= q && j <= r)
    {
      if (A[i] <= A[j])
        tmp.push_back(A[i++]);
      else
        tmp.push_back(A[j++]);
    }

    tmp.insert(tmp.end(), A.begin() + i, A.begin() + q + 1);
    tmp.insert(tmp.end(), A.begin() + j, A.begin() + r + 1);

    copy(tmp.begin(), tmp.end(), A.begin() + p);
  };

  auto merge_sort = [&](auto &&self, int p, int r) -> void
  {
    if (p >= r)
      return;
    int q = (p + r) >> 1;
    self(self, p, q);
    self(self, q + 1, r);
    merge(p, q, r);
  };

  merge_sort(merge_sort, 0, N - 1);
  for (int &number : A)
    cout << number;

  return 0;
}
