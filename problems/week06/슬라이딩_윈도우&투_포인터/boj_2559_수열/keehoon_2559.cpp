// 2559 – 수열
// https://www.acmicpc.net/problem/2559
// solved.ac: https://solved.ac/search?query=2559
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver III
// 태그: 누적 합, 두 포인터, 슬라이딩 윈도우
// 푼 사람 수: 23,720
// 평균 시도: 2.67

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
  vector<int> temperatures(N);
  for (int &temperature : temperatures)
    cin >> temperature;

  int result = -1e7;
  int tmp = 0;
  for (int i = 0; i < N; ++i)
  {
    tmp += i >= K ? temperatures[i] - temperatures[i - K] : temperatures[i];
    result = i >= K - 1 ? max(result, tmp) : result;
  }

  cout << result;

  return 0;
}
