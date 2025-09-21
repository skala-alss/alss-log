// 27496 – 발머의 피크 이론
// https://www.acmicpc.net/problem/27496
// solved.ac: https://solved.ac/search?query=27496
// 시간 제한: 1 초 (추가 시간 없음)
// 메모리 제한: 1024 MB
// 티어: ⚪ Silver III
// 태그: 누적 합, 슬라이딩 윈도우
// 푼 사람 수: 722
// 평균 시도: 2.39

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

  int N, L;
  cin >> N >> L;
  vector<int> alcohol(N);
  for (int &amount : alcohol)
    cin >> amount;

  int cnt = 0;
  int window = 0;
  for (int i = 0; i < N; ++i)
  {
    window += i >= L ? alcohol[i] - alcohol[i - L] : alcohol[i];
    129 <= window &&window <= 138 && ++cnt;
  }

  cout << cnt;

  return 0;
}
