// 4386 – 별자리 만들기
// https://www.acmicpc.net/problem/4386
// solved.ac: https://solved.ac/search?query=4386
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: 🟡 Gold III
// 태그: 그래프 이론, 최소 스패닝 트리
// 푼 사람 수: 9,971
// 평균 시도: 1.69

#include <cmath>
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

  int n;
  cin >> n;
  vector<pair<double, double>> stars(n);
  for (auto &star : stars)
    cin >> star.first >> star.second;

  vector<vector<double>> adjacency_matrix(n, vector<double>(n, 0));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      adjacency_matrix[i][j] = hypot(stars[i].first - stars[j].first, stars[i].second - stars[j].second);

  vector<bool> visited(n, false);
  priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
  pq.emplace(0, 0);
  double result = 0;
  int cnt = 0;
  while (!pq.empty() && cnt < n)
  {
    auto [w, u] = pq.top();
    pq.pop();
    if (visited[u])
      continue;
    visited[u] = true;
    result += w;
    ++cnt;

    for (int i = 0; i < n; ++i)
      if (!visited[i])
        pq.emplace(adjacency_matrix[u][i], i);
  }

  cout << result;

  return 0;
}
