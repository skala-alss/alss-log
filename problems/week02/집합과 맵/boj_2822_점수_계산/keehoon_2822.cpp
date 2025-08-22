// 2822 – 점수 계산
// https://www.acmicpc.net/problem/2822
// solved.ac: https://solved.ac/search?query=2822
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver V
// 태그: 정렬
// 푼 사람 수: 11,467
// 평균 시도: 1.35

#include <iostream>
#include <set>
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

  set<pair<int, int>, greater<>> scores;
  set<int> indices;

  for (int i = 1; i <= 8; ++i)
  {
    int score;
    cin >> score;
    scores.insert(make_pair(score, i));
  }

  int result = 0;
  for (auto it = scores.begin(); it != next(scores.begin(), 5); ++it)
  {
    result += it->first;
    indices.insert(it->second);
  }
  cout << result << '\n';
  for (int index : indices)
    cout << index << ' ';
  return 0;
}
