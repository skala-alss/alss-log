// 1543 – 문서 검색
// https://www.acmicpc.net/problem/1543
// solved.ac: https://solved.ac/search?query=1543
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver V
// 태그: 문자열, 브루트포스 알고리즘
// 푼 사람 수: 12,693
// 평균 시도: 2.19

#include <iostream>
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

  string document, word;
  getline(cin, document);
  getline(cin, word);

  int cnt = 0;
  int l = 0;
  int doc_len = document.length();
  int len = word.length();
  while (l + len <= doc_len)
  {
    if (document.compare(l, len, word) == 0)
    {
      ++cnt;
      l += len;
    }
    else
      ++l;
  }

  cout << cnt;
  return 0;
}
