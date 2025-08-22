// 11478 – 서로 다른 부분 문자열의 개수
// https://www.acmicpc.net/problem/11478
// solved.ac: https://solved.ac/search?query=11478
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver III
// 태그: 문자열, 자료 구조, 집합과 맵, 트리를 사용한 집합과 맵, 해시를 사용한 집합과 맵
// 푼 사람 수: 21,364
// 평균 시도: 1.56

#include <iostream>
#include <string>
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

  string S;
  cin >> S;

  unordered_set<string> substrings;

  int n = S.length();

  for (int i = 0; i < n; ++i)
    for (int j = 1; j <= n - i; ++j)
      substrings.insert(S.substr(i, j));

  cout << substrings.size();

  return 0;
}
