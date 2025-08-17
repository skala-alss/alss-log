// 10815 – 숫자 카드
// https://www.acmicpc.net/problem/10815
// solved.ac: https://solved.ac/search?query=10815
// 시간 제한: 2 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver V
// 태그: 이분 탐색, 자료 구조, 정렬, 집합과 맵, 해시를 사용한 집합과 맵
// 푼 사람 수: 46,257
// 평균 시도: 2.32

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

  int N, M;
  unordered_set<int> s;

  cin >> N;
  while (N--)
  {
    int number;
    cin >> number;
    s.insert(number);
  }

  cin >> M;
  while (M--)
  {
    int number;
    cin >> number;
    cout << (s.count(number) ? 1 : 0) << ' ';
  }
}
