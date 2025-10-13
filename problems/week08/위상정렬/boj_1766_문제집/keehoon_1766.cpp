// 1766 – 문제집
// https://www.acmicpc.net/problem/1766
// solved.ac: https://solved.ac/search?query=1766
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: 🟡 Gold II
// 태그: 그래프 이론, 방향 비순환 그래프, 우선순위 큐, 위상 정렬, 자료 구조
// 푼 사람 수: 14,831
// 평균 시도: 2.00

#include <iostream>
#include <vector>
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

  int N, M;
  cin >> N >> M;

  vector<vector<int>> adjacency_list(N + 1);
  vector<int> in_degrees(N + 1, 0);
  while (M--)
  {
    int A, B;
    cin >> A >> B;
    adjacency_list[A].push_back(B);
    ++in_degrees[B];
  }

  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 1; i <= N; ++i)
    if (in_degrees[i] == 0)
      pq.push(i);

  while (!pq.empty())
  {
    int cur = pq.top();
    pq.pop();
    cout << cur << ' ';

    for (int &nxt : adjacency_list[cur])
      if (--in_degrees[nxt] == 0)
        pq.push(nxt);
  }

  return 0;
}
