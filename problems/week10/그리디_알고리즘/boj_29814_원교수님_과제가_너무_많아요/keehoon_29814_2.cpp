// 29814 – 원교수님 과제가 너무 많아요
// https://www.acmicpc.net/problem/29814
// solved.ac: https://solved.ac/search?query=29814
// 시간 제한: 1 초
// 메모리 제한: 1024 MB
// 티어: 🟡 Gold I
// 태그: 그리디 알고리즘, 분리 집합, 우선순위 큐, 자료 구조, 정렬
// 푼 사람 수: 60
// 평균 시도: 3.02

#include <algorithm>
#include <iostream>
#include <numeric>
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

  struct Assignment
  {
    int start, point;
    Assignment() : start(0), point(0) {}
    Assignment(int start, int point) : start(start), point(point) {}

    bool operator<(const Assignment &other) const
    {
      return point > other.point;
    }
  };

  struct DSU
  {
    vector<int> parent;
    DSU(int n)
    {
      parent.resize(n + 1);
      iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }

    void use(int x)
    {
      parent[find(x)] = find(x - 1);
    }
  };

  int N, C;
  cin >> N >> C;

  vector<Assignment> assignments(N);
  for (int i = 0; i < N; ++i)
  {
    int d, t, p;
    cin >> d >> t >> p;
    assignments[i] = Assignment(d - t + 1, p);
  }

  sort(assignments.begin(), assignments.end());

  DSU dsu(N);
  vector<int> picked;
  picked.reserve(N);
  int result = 0;

  for (const auto &assignment : assignments)
  {
    int start = assignment.start;
    int u = dsu.find(start);

    if (u == 0)
      continue;

    picked.push_back(assignment.point);
    result += assignment.point;
    dsu.use(u);
  }

  if (result < C)
  {
    cout << "I'm sorry professor Won!";
    return 0;
  }

  int sum = 0;
  for (int i = 0; i < picked.size(); ++i)
  {
    sum += picked[i];
    if (sum >= C)
    {
      cout << i + 1;
      return 0;
    }
  }

  return 0;
}
