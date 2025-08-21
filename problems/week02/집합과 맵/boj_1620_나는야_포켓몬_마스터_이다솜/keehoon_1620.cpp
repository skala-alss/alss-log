// 1620 – 나는야 포켓몬 마스터 이다솜
// https://www.acmicpc.net/problem/1620
// solved.ac: https://solved.ac/search?query=1620
// 시간 제한: 2 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver IV
// 태그: 자료 구조, 집합과 맵, 해시를 사용한 집합과 맵
// 푼 사람 수: 41,437
// 평균 시도: 2.80

#include <algorithm>
#include <iostream>
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

  unordered_map<string, string> pokedex_by_name;
  unordered_map<string, string> pokedex_by_id;

  int id = 0;
  while (N--)
  {
    ++id;
    string name;
    cin >> name;
    pokedex_by_name.insert(make_pair(name, to_string(id)));
    pokedex_by_id.insert(make_pair(to_string(id), name));
  }

  while (M--)
  {
    string query;
    cin >> query;

    cout << (all_of(query.begin(), query.end(), ::isdigit) ? pokedex_by_id[query] : pokedex_by_name[query]) << '\n';
  }
  return 0;
}
