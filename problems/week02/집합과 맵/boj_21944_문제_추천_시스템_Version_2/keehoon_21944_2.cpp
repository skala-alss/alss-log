// 21944 – 문제 추천 시스템 Version 2
// https://www.acmicpc.net/problem/21944
// solved.ac: https://solved.ac/search?query=21944
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold II
// 태그: 자료 구조, 집합과 맵, 트리를 사용한 집합과 맵
// 푼 사람 수: 748
// 평균 시도: 3.47

#include <iostream>
#include <set>
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

  using lv_pid = pair<int, int>;
  const int MAX_PID = 1e5 + 1;

  int N;
  cin >> N;

  vector<set<lv_pid>> problems1(101);
  set<lv_pid> problems2;
  vector<lv_pid> meta(1e5 + 1);
  while (N--)
  {
    int P, L, G;
    cin >> P >> L >> G;

    problems1[G].emplace(L, P);
    problems2.emplace(L, P);
    meta[P] = make_pair(L, G);
  }

  int M;
  cin >> M;
  while (M--)
  {
    string command;
    cin >> command;

    if (command == "recommend")
    {
      int G, x;
      cin >> G >> x;
      cout << (x == 1 ? problems1[G].rbegin()->second : problems1[G].begin()->second) << '\n';
    }

    else if (command == "recommend2")
    {
      int x;
      cin >> x;
      cout << (x == 1 ? problems2.rbegin()->second : problems2.begin()->second) << '\n';
    }

    else if (command == "recommend3")
    {
      int x, L;
      cin >> x >> L;
      cout << (x == 1
                   ? (problems2.lower_bound(make_pair(L, 0)) != problems2.end()
                          ? problems2.lower_bound(make_pair(L, 0))->second
                          : -1)
                   : (problems2.lower_bound(make_pair(L, 0)) != problems2.begin()
                          ? prev(problems2.lower_bound(make_pair(L, 0)))->second
                          : -1))
           << '\n';
    }

    else if (command == "add")
    {
      int P, L, G;
      cin >> P >> L >> G;
      problems1[G].emplace(L, P);
      problems2.emplace(L, P);
      meta[P] = make_pair(L, G);
    }

    else if (command == "solved")
    {
      int P, L, G;
      cin >> P;
      L = meta[P].first;
      G = meta[P].second;
      problems1[G].erase(make_pair(L, P));
      problems2.erase(make_pair(L, P));
    }
  }

  return 0;
}
