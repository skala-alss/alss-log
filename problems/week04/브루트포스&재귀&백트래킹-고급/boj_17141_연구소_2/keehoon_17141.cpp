// 17141 – 연구소 2
// https://www.acmicpc.net/problem/17141
// solved.ac: https://solved.ac/search?query=17141
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold IV
// 태그: 격자 그래프, 그래프 이론, 그래프 탐색, 너비 우선 탐색, 브루트포스 알고리즘
// 푼 사람 수: 4,336
// 평균 시도: 2.36

#include <iostream>
#include <queue>
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

  int N, M;
  cin >> N >> M;
  vector<int> lab(N * N);
  queue<int> pods;
  for (int i = 0; i < N * N; ++i)
  {
    cin >> lab[i];
    if (lab[i] == 2)
    {
      pods.push(i);
      lab[i] = 0;
    }
  }

  return 0;
}
