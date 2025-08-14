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
#include <queue>
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

  int N, number;

  cin >> N;

  priority_queue<int, vector<int>, greater<int>> pq;

  for (int i = 1; i <= N * N; ++i)
  {
    cin >> number;
    pq.push(number);
    if (pq.size() > N)
      pq.pop();
  }

  cout << pq.top();
  return 0;
}
