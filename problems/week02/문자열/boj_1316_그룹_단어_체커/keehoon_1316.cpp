// 1316 – 그룹 단어 체커
// https://www.acmicpc.net/problem/1316
// solved.ac: https://solved.ac/search?query=1316
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver V
// 태그: 구현, 문자열
// 푼 사람 수: 86,255
// 평균 시도: 1.84

#include <algorithm>
#include <iostream>
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
  int group_word = 0;
  cin >> N;

  while (N--)
  {
    string word;
    cin >> word;

    vector<int> groups(26, 0);
    int l = 0, r = 0;

    while (l < word.length())
    {
      while (r < word.length() && word[l] == word[r])
        ++r;

      ++groups[word[l] - 'a'];
      l = r;
    }

    if (*max_element(groups.begin(), groups.end()) <= 1)
      ++group_word;
  }

  cout << group_word;
  return 0;
}
