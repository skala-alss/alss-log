// 23881 – 알고리즘 수업 - 선택 정렬 1
// https://www.acmicpc.net/problem/23881
// solved.ac: https://solved.ac/search?query=23881
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟫 Bronze I
// 태그: 구현, 시뮬레이션, 정렬
// 푼 사람 수: 1,781
// 평균 시도: 2.54

#include <algorithm>
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

  vector<int> sequence(N);
  for (int &term : sequence)
    cin >> term;

  for (int last = N - 1; last >= 0; --last)
  {
    auto max_it = max_element(sequence.begin(), sequence.begin() + last + 1);
    int idx = distance(sequence.begin(), max_it);

    if (idx != last)
    {
      --K;
      if (!K)
      {
        cout << min(sequence[idx], sequence[last]) << ' ' << max(sequence[idx], sequence[last]);
        return 0;
      }

      iter_swap(sequence.begin() + idx, sequence.begin() + last);
    }
  }

  cout << -1;

  return 0;
}
