// 30010 – 잘못된 버블정렬
// https://www.acmicpc.net/problem/30010
// solved.ac: https://solved.ac/search?query=30010
// 시간 제한: 1 초 (추가 시간 없음)
// 메모리 제한: 1024 MB (추가 메모리 없음)
// 티어: ⚪ Silver V
// 태그: 애드 혹, 해 구성하기
// 푼 사람 수: 457
// 평균 시도: 1.28

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

  int N;
  cin >> N;

  for (int i = 0; i < N; ++i)
    cout << (i > 0 ? N - 1 : N) << ' ';

  return 0;
}
