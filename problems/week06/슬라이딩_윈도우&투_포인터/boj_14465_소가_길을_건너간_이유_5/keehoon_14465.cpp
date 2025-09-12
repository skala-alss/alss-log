// 14465 – 소가 길을 건너간 이유 5
// https://www.acmicpc.net/problem/14465
// solved.ac: https://solved.ac/search?query=14465
// 시간 제한: 2 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver II
// 태그: 누적 합, 슬라이딩 윈도우
// 푼 사람 수: 2,602
// 평균 시도: 2.11

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

  int N, K, B;
  cin >> N >> K >> B;
  vector<bool> crosswalks(N + 1);
  while (B--)
  {
    int idx;
    cin >> idx;
    crosswalks[idx] = true;
  }

  int min_blinker = K;
  int window = 0;
  for (int i = 1; i <= N; ++i)
  {
    window += i > K ? crosswalks[i] - crosswalks[i - K] : crosswalks[i];
    min_blinker = i >= K ? min(min_blinker, window) : min_blinker;
    if (!min_blinker)
      break;
  }

  cout << min_blinker;

  return 0;
}
