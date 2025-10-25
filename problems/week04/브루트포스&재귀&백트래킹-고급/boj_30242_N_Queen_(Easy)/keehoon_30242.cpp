// 30242 – 🧩 N-Queen (Easy)
// https://www.acmicpc.net/problem/30242
// solved.ac: https://solved.ac/search?query=30242
// 시간 제한: 0.5 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold III
// 태그: 백트래킹
// 푼 사람 수: 121
// 평균 시도: 2.60

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

  int N;
  vector<int> cols(N);
  for (int &col : cols)
    cin >> col;
  return 0;
}
