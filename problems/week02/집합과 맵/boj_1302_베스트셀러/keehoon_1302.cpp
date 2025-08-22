// 1302 – 베스트셀러
// https://www.acmicpc.net/problem/1302
// solved.ac: https://solved.ac/search?query=1302
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver IV
// 태그: 문자열, 자료 구조, 정렬, 집합과 맵, 해시를 사용한 집합과 맵
// 푼 사람 수: 14,787
// 평균 시도: 1.81

#include <algorithm>
#include <iostream>
#include <map>
#if defined(_WIN32)
#include <io.h>
#include <cstdio>
#else
#include <unistd.h>
#include <cstdio>
#endif

using namespace std;

struct Compare
{
  bool operator()(const pair<string, int> &a, const pair<string, int> &b) const
  {
    if (a.second != b.second)
      return a.second < b.second;
    return a.first > b.first;
  }
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

  int N;
  cin >> N;

  map<string, int> record;

  while (N--)
  {
    string title;
    cin >> title;
    ++record[title];
  }

  string best = (*max_element(record.begin(), record.end(), Compare())).first;
  cout << best;
  return 0;
}
