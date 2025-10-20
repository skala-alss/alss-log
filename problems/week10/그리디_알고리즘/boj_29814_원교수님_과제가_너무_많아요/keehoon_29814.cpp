// 29814 – 원교수님 과제가 너무 많아요
// https://www.acmicpc.net/problem/29814
// solved.ac: https://solved.ac/search?query=29814
// 시간 제한: 1 초
// 메모리 제한: 1024 MB
// 티어: 🟡 Gold I
// 태그: 그리디 알고리즘, 분리 집합, 우선순위 큐, 자료 구조, 정렬
// 푼 사람 수: 60
// 평균 시도: 3.02

#include <iostream>
#include <vector>
#include <map>
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

  int N, C;
  cin >> N >> C;

  map<int, vector<int>> assignments;

  while (N--)
  {
    int d, t, p;
    cin >> d >> t >> p;
    assignments[d - t + 1].push_back(p);
  }

  int sum = 0;
  priority_queue<int, vector<int>, greater<int>> pq;
  for (const pair<int, vector<int>> &assignment : assignments)
  {
    int day = assignment.first;
    vector<int> points = assignment.second;
    for (int &point : points)
    {
      sum += point;
      pq.push(point);
    }

    while (pq.size() > day)
    {
      sum -= pq.top();
      pq.pop();
    }
  }

  if (sum < C)
  {
    cout << "I'm sorry professor Won!";
    return 0;
  }

  while (sum >= C)
  {
    sum -= pq.top();
    pq.pop();
  }

  cout << pq.size() + 1;

  return 0;
}
