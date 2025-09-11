// 21939 – 문제 추천 시스템 Version 1
// https://www.acmicpc.net/problem/21939
// solved.ac: https://solved.ac/search?query=21939
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: 🟡 Gold IV
// 태그: 우선순위 큐, 자료 구조, 집합과 맵, 트리를 사용한 집합과 맵, 해시를 사용한 집합과 맵
// 푼 사람 수: 2,506
// 평균 시도: 2.96

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

  int N;
  cin >> N;

  set<pair<int, int>> p_list;
  vector<int> levels(1e5 + 1);

  while (N--)
  {
    int P, L;
    cin >> P >> L;
    p_list.emplace(L, P);
    levels[P] = L;
  }

  int M;
  cin >> M;
  while (M--)
  {
    string command;
    cin >> command;

    if (command == "recommend")
    {
      int option;
      cin >> option;
      cout << (option == 1 ? p_list.rbegin()->second : p_list.begin()->second) << '\n';
    }

    else if (command == "add")
    {
      int P, L;
      cin >> P >> L;
      p_list.emplace(L, P);
      levels[P] = L;
    }

    else if (command == "solved")
    {
      int P;
      cin >> P;
      p_list.erase(make_pair(levels[P], P));
      levels[P] = 0;
    }
  }

  return 0;
}
