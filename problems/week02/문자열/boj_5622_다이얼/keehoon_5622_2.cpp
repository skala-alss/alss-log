// 5622 – 다이얼
// https://www.acmicpc.net/problem/5622
// solved.ac: https://solved.ac/search?query=5622
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: 🟫 Bronze II
// 태그: 구현
// 푼 사람 수: 84,138
// 평균 시도: 1.71

#include <iostream>
#include <vector>
#include <numeric>
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

  string S;
  cin >> S;

  vector<int> dial = {3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6,
                      7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10};

  int result = accumulate(S.begin(), S.end(), 0, [&](int acc, char c)
                          { return acc + dial[c - 'A']; });

  cout << result;

  return 0;
}
