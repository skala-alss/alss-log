// 23309 – 철도 공사
// https://www.acmicpc.net/problem/23309
// solved.ac: https://solved.ac/search?query=23309
// 시간 제한: 2 초 (추가 시간 없음)
// 메모리 제한: 512 MB (추가 메모리 없음)
// 티어: 🟡 Gold IV
// 태그: 구현, 연결 리스트, 자료 구조
// 푼 사람 수: 617
// 평균 시도: 4.56

#include <iostream>
#include <list>
#include <unordered_map>
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

  list<int> route_map;
  unordered_map<int, list<int>::iterator> pts;
  pts.reserve(N * 2);

  for (int i = 1; i <= N; ++i)
  {
    int station;
    cin >> station;
    route_map.push_back(station);
    pts[station] = prev(route_map.end());
  }

  while (M--)
  {
    string code;
    cin >> code;

    if (code == "BN")
    {
      int current_station, new_station;
      cin >> current_station >> new_station;
      auto right = next(pts[current_station]) != route_map.end() ? next(pts[current_station]) : route_map.begin();
      cout << *right << '\n';
      pts[new_station] = route_map.insert(right, new_station);
    }
    else if (code == "BP")
    {
      int current_station, new_station;
      cin >> current_station >> new_station;
      auto left = pts[current_station] != route_map.begin() ? prev(pts[current_station]) : prev(route_map.end());
      cout << *left << '\n';
      pts[new_station] = route_map.insert(next(left), new_station);
    }
    else if (code == "CP")
    {
      int current_station;
      cin >> current_station;
      auto left = pts[current_station] != route_map.begin() ? prev(pts[current_station]) : prev(route_map.end());
      cout << *left << '\n';
      pts.erase(*left);
      route_map.erase(left);
    }
    else if (code == "CN")
    {
      int current_station;
      cin >> current_station;
      auto right = next(pts[current_station]) != route_map.end() ? next(pts[current_station]) : route_map.begin();
      cout << *right << '\n';
      pts.erase(*right);
      route_map.erase(right);
    }
  }

  return 0;
}
