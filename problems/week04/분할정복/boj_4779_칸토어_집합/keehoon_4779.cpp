// 4779 – 칸토어 집합
// https://www.acmicpc.net/problem/4779
// solved.ac: https://solved.ac/search?query=4779
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver III
// 태그: 분할 정복, 재귀
// 푼 사람 수: 10,509
// 평균 시도: 2.19

#include <iostream>
#include <cmath>
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
  while (cin >> N)
  {
    int len = int(pow(3, N));

    auto dnq = [](auto &&self, int sz) -> void
    {
      if (sz == 1)
      {
        cout << '-';
        return;
      }
      sz /= 3;
      self(self, sz);
      string spaces(sz, ' ');
      cout << spaces;
      self(self, sz);
    };

    dnq(dnq, len);
    cout << '\n';
  }
  return 0;
}
