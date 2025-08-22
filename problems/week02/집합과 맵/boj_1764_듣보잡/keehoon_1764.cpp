// 1764 – 듣보잡
// https://www.acmicpc.net/problem/1764
// solved.ac: https://solved.ac/search?query=1764
// 시간 제한: 2 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver IV
// 태그: 문자열, 자료 구조, 정렬, 집합과 맵, 해시를 사용한 집합과 맵
// 푼 사람 수: 49,817
// 평균 시도: 2.37

#include <algorithm>
#include <iostream>
#include <set>
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

  set<string> not_seen;
  set<string> not_heard;

  while (N--)
  {
    string name;
    cin >> name;
    not_seen.insert(name);
  }

  while (M--)
  {
    string name;
    cin >> name;
    not_heard.insert(name);
  }

  set<string> result;

  set_intersection(not_seen.begin(), not_seen.end(),
                   not_heard.begin(), not_heard.end(),
                   inserter(result, result.begin()));

  cout << result.size() << '\n';
  for (string name : result)
    cout << name << '\n';
  return 0;
}
