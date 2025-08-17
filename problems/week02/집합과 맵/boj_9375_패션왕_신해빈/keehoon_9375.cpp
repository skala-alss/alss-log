// 9375 – 패션왕 신해빈
// https://www.acmicpc.net/problem/9375
// solved.ac: https://solved.ac/search?query=9375
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver III
// 태그: 수학, 자료 구조, 조합론, 집합과 맵, 해시를 사용한 집합과 맵
// 푼 사람 수: 25,520
// 평균 시도: 1.77

#include <iostream>
#include <unordered_map>
#include <unordered_set>
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

  int T;
  cin >> T;

  while (T--)
  {
    int N;
    cin >> N;

    unordered_map<string, unordered_set<string>> closet;

    while (N--)
    {
      string name, type;
      cin >> name >> type;
      closet[type].insert(name);
    }

    int result = 1;
    for (auto &type : closet)
      result *= type.second.size() + 1;

    cout << result - 1 << '\n';
  }
  return 0;
}
