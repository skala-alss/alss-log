// 16401 – 과자 나눠주기
// https://www.acmicpc.net/problem/16401
// solved.ac: https://solved.ac/search?query=16401
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver II
// 태그: 매개 변수 탐색, 이분 탐색
// 푼 사람 수: 4,975
// 평균 시도: 2.69

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

  int M, N;
  cin >> M >> N;
  vector<int> sticks(N);
  int l = 1, r = 0;
  for (int &stick : sticks)
  {
    cin >> stick;
    r = max(r, stick);
  }

  int max_len = 0;
  while (l <= r)
  {
    int mid = (l + r) / 2;
    int cnt = 0;
    for (int &stick : sticks)
      cnt += stick / mid;

    if (cnt >= M)
    {
      max_len = mid;
      l = mid + 1;
    }

    else if (cnt < M)
      r = mid - 1;
  }

  cout << max_len;

  return 0;
}
