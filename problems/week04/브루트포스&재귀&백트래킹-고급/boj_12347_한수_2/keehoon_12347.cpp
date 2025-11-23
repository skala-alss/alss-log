// 12347 – 한수 2
// https://www.acmicpc.net/problem/12347
// solved.ac: https://solved.ac/search?query=12347
// 시간 제한: 0.5 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold V
// 태그: 브루트포스 알고리즘, 수학
// 푼 사람 수: 89
// 평균 시도: 2.33

#include <iostream>
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

  long long N;
  cin >> N;

  long long result = 0;
  for (int i = 1; i < 10; ++i)
  {
    if (i > N)
      break;
    ++result;
    for (int j = 0; j < 10; ++j)
    {
      string tmp = to_string(i) + to_string(j);
      if (stoll(tmp) > N)
        break;
      ++result;
      int diff = j - i;
      int prv = j;

      while (true)
      {
        prv += diff;
        tmp += to_string(prv);
        if (prv > 9 || prv < 0 || tmp.length() > 18 || stoll(tmp) > N)
          break;
        ++result;
      }
    }
  }

  cout << result;

  return 0;
}
