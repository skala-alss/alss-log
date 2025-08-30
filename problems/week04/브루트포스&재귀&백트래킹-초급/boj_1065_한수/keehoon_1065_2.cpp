// 1065 – 한수
// https://www.acmicpc.net/problem/1065
// solved.ac: https://solved.ac/search?query=1065
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver IV
// 태그: 브루트포스 알고리즘, 수학
// 푼 사람 수: 72,230
// 평균 시도: 1.81

#include <iostream>
#include <unordered_set>
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

  int result = 0;
  for (int i = 1; i <= N; ++i)
  {
    int current = i;
    int prev = current % 10;
    current /= 10;
    int diff = prev - current % 10;
    bool valid = true;

    while (current > 0)
    {
      int next = current % 10;
      if (prev - next != diff)
      {
        valid = false;
        break;
      }
      prev = next;
      current /= 10;
    }

    if (valid)
      ++result;
  }

  cout << result;
  return 0;
}
