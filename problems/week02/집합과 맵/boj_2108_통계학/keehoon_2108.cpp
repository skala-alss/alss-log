// 2108 – 통계학
// https://www.acmicpc.net/problem/2108
// solved.ac: https://solved.ac/search?query=2108
// 시간 제한: 2 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver II
// 태그: 구현, 수학, 정렬
// 푼 사람 수: 40,714
// 평균 시도: 3.60

#include <cmath>
#include <iostream>
#include <numeric>
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

  vector<int> dat(8001, 0);
  int total = 0;
  int average;
  int numbers = 0;
  int median;
  int mode = 0;
  int max_count = 0;
  bool is_second = false;
  int min_val = 4001;
  int max_val = -4001;

  for (int i = 1; i <= N; ++i)
  {
    int number;
    cin >> number;
    min_val = min(min_val, number);
    max_val = max(max_val, number);
    ++dat[number + 4000];
  }

  for (int i = 0; i <= 8000; ++i)
  {
    total += dat[i] * (i - 4000);

    if (numbers < N / 2 + 1)
    {
      numbers += dat[i];
      if (numbers >= N / 2 + 1)
        median = i - 4000;
    }

    if (max_count < dat[i])
    {
      max_count = dat[i];
      mode = i - 4000;
      is_second = false;
    }

    else if (max_count == dat[i] && !is_second)
    {
      max_count = dat[i];
      mode = i - 4000;
      is_second = true;
    }
  }

  average = round((double)total / N);

  cout << average << '\n'
       << median << '\n'
       << mode << '\n'
       << max_val - min_val;
  return 0;
}
