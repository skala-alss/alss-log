// 1213 – 팰린드롬 만들기
// https://www.acmicpc.net/problem/1213
// solved.ac: https://solved.ac/search?query=1213
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver III
// 태그: 구현, 그리디 알고리즘, 문자열, 홀짝성
// 푼 사람 수: 12,495
// 평균 시도: 2.28

#include <algorithm>
#include <vector>
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

  string name;
  cin >> name;

  vector<int> dat(26);

  for (char l : name)
    ++dat[l - 'A'];

  int odds = 0;
  for (int cnt : dat)
    if (cnt & 1)
      ++odds;

  if (odds > 1)
    cout << "I'm Sorry Hansoo";

  else
  {
    for (int i = 0; i < 26; ++i)
      for (int j = 1; j <= dat[i] / 2; ++j)
        cout << (char)('A' + i);
    auto it = find_if(dat.begin(), dat.end(), [&](int cnt)
                      { return cnt & 1; });

    if (odds)
      cout << (char)('A' + it - dat.begin());

    for (int i = 25; i > -1; --i)
      for (int j = 1; j <= dat[i] / 2; ++j)
        cout << (char)('A' + i);
  }

  return 0;
}
