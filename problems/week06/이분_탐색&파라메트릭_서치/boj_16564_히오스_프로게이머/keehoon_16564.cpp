// 16564 – 히오스 프로게이머
// https://www.acmicpc.net/problem/16564
// solved.ac: https://solved.ac/search?query=16564
// 시간 제한: 2 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver I
// 태그: 매개 변수 탐색, 이분 탐색
// 푼 사람 수: 1,655
// 평균 시도: 2.96

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
  vector<int> characters(N);
  int l = 1e9;
  for (int &character : characters)
  {
    cin >> character;
    l = min(l, character);
  }

  int r = l + K;
  int objective_level;
  while (l <= r)
  {
    int mid = l + (r - l) / 2;
    long long used = 0;
    for (int &character : characters)
      if (character < mid)
        used += mid - character;

    if (used <= K)
    {
      objective_level = mid;
      l = mid + 1;
    }

    else
      r = mid - 1;
  }

  cout << objective_level;

  return 0;
}
