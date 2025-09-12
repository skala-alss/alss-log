// 12847 – 꿀 아르바이트
// https://www.acmicpc.net/problem/12847
// solved.ac: https://solved.ac/search?query=12847
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver III
// 태그: 누적 합, 슬라이딩 윈도우
// 푼 사람 수: 2,384
// 평균 시도: 2.64

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

  int n, m;
  cin >> n >> m;
  vector<int> wages(n);
  for (int &wage : wages)
    cin >> wage;

  long long max_wage = 0;
  long long window = 0;
  for (int i = 0; i < n; ++i)
  {
    window += i >= m ? wages[i] - wages[i - m] : wages[i];
    max_wage = i >= m - 1 ? max(max_wage, window) : max_wage;
  }

  cout << max_wage;

  return 0;
}
