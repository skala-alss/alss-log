// 1966 – 프린터 큐
// https://www.acmicpc.net/problem/1966
// solved.ac: https://solved.ac/search?query=1966
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver III
// 태그: 구현, 시뮬레이션, 자료 구조, 큐
// 푼 사람 수: 43,677
// 평균 시도: 1.69

#include <array>
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

struct Document
{
  int priority;
  int index;
};

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

  int T;
  cin >> T;

  for (int tc = 1; tc <= T; ++tc)
  {
    int N, M;
    cin >> N >> M;

    array<int, 10> counter{};
    queue<Document> q;

    for (int i = 0; i < N; ++i)
    {
      int p;
      cin >> p;
      ++counter[p];
      q.push({p, i});
    }

    int order = 1;
    int max_priority = 9;
    while (!q.empty())
    {
      while (max_priority > 0 && counter[max_priority] == 0)
        --max_priority;

      auto current = q.front();
      q.pop();

      if (current.priority < max_priority)
        q.push(current);
      else
      {
        --counter[max_priority];
        if (current.index == M)
        {
          cout << order << '\n';
          break;
        }
        ++order;
      }
    }
  }
  return 0;
}
