// 1919 – 애너그램 만들기
// https://www.acmicpc.net/problem/1919
// solved.ac: https://solved.ac/search?query=1919
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: 🟫 Bronze II
// 태그: 구현, 문자열
// 푼 사람 수: 10,141
// 평균 시도: 1.68

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

  string A, B;
  cin >> A >> B;

  vector<int> cnt(26);

  for (char l : A)
    ++cnt[l - 'a'];

  for (char l : B)
    --cnt[l - 'a'];

  int rm = 0;
  for (int x : cnt)
    rm += abs(x);

  cout << rm;
  return 0;
}
