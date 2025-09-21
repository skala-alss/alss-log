// 15565 – 귀여운 라이언
// https://www.acmicpc.net/problem/15565
// solved.ac: https://solved.ac/search?query=15565
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver I
// 태그: 두 포인터, 슬라이딩 윈도우
// 푼 사람 수: 2,750
// 평균 시도: 2.58

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
  vector<int> line(N);
  for (int &doll : line)
    cin >> doll;

  int minimum_size = N + 1;
  int l = 0, cnt1 = 0;
  for (int r = 0; r < N; ++r)
  {
    if (line[r] == 1)
      ++cnt1;

    while (cnt1 >= K)
    {
      minimum_size = min(minimum_size, r - l + 1);
      if (line[l] == 1)
        --cnt1;
      ++l;
    }
  }

  cout << (minimum_size != N + 1 ? minimum_size : -1);

  return 0;
}
