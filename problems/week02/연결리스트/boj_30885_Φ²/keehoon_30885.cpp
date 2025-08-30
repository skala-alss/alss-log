// 30885 – Φ²
// https://www.acmicpc.net/problem/30885
// solved.ac: https://solved.ac/search?query=30885
// 시간 제한: 1 초
// 메모리 제한: 1024 MB
// 티어: 🟡 Gold IV
// 태그: 구현, 시뮬레이션, 연결 리스트, 자료 구조
// 푼 사람 수: 225
// 평균 시도: 3.28

#include <iostream>
#include <list>
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

  list<pair<long long, int>> microorganisms;
  for (int i = 1; i <= N; ++i)
  {
    long long microorganism;
    cin >> microorganism;
    microorganisms.push_back(make_pair(microorganism, i));
  }

  while (microorganisms.size() > 1)
  {
    for (auto it = microorganisms.begin(); it != microorganisms.end(); ++it)
    {
      long long current = it->first;
      if (it != microorganisms.begin() && current >= prev(it)->first)
      {
        it->first += prev(it)->first;
        microorganisms.erase(prev(it));
      }

      if (next(it) != microorganisms.end() && current >= next(it)->first)
      {
        it->first += next(it)->first;
        microorganisms.erase(next(it));
      }
    }
  }

  cout << microorganisms.begin()->first << '\n'
       << microorganisms.begin()->second;

  return 0;
}
