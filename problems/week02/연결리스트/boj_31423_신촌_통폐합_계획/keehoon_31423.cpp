// 31423 – 신촌 통폐합 계획
// https://www.acmicpc.net/problem/31423
// solved.ac: https://solved.ac/search?query=31423
// 시간 제한: 2 초 (추가 시간 없음)
// 메모리 제한: 1024 MB (추가 메모리 없음)
// 티어: 🟡 Gold V
// 태그: 그래프 이론, 그래프 탐색, 깊이 우선 탐색, 문자열, 연결 리스트, 자료 구조
// 푼 사람 수: 407
// 평균 시도: 4.12

#include <iostream>
#include <list>
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

  using Iter = list<string>::iterator;
  vector<pair<Iter, Iter>> pointers(N + 1);

  list<string> united_name;

  for (int i = 1; i <= N; ++i)
  {
    string name;
    cin >> name;
    united_name.push_back(name);
    pointers[i].first = prev(united_name.end());
    pointers[i].second = prev(united_name.end());
  }

  for (int k = 1; k < N; ++k)
  {
    int i, j;
    cin >> i >> j;

    if (next(pointers[i].second) == pointers[j].first)
      pointers[i].second = pointers[j].second;
    else
    {
      united_name.splice(next(pointers[i].second), united_name, pointers[j].first, next(pointers[j].second));
      pointers[i].second = pointers[j].second;
    }
  }

  for (string &name : united_name)
    cout << name;
  return 0;
}
