// 2075 – N번째 큰 수
// https://www.acmicpc.net/problem/2075
// solved.ac: https://solved.ac/search?query=2075
// 시간 제한: 1 초
// 메모리 제한: 12 MB ( 하단 참고 )
// 티어: ⚪ Silver III
// 태그: 우선순위 큐, 자료 구조, 정렬
// 푼 사람 수: 14,091
// 평균 시도: 2.53

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

  int N;
  cin >> N;
  multiset<int> ms;

  for (int i = 0; i < N * N; ++i)
  {
    int x;
    cin >> x;
    ms.insert(x);
    if ((int)ms.size() > N)
      ms.erase(ms.begin()); // 가장 작은 원소 제거
  }
  cout << *ms.begin() << '\n'; // N번째 큰 수(= 상위 N개 중 최솟값)
}