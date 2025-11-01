// 34094 – 골드리치의 비밀 금고
// https://www.acmicpc.net/problem/34094
// solved.ac: https://solved.ac/search?query=34094
// 시간 제한: 2 초 (추가 시간 없음)
// 메모리 제한: 1024 MB (추가 메모리 없음)
// 티어: 🟡 Gold V
// 태그: 애드 혹, 정렬, 해 구성하기
// 푼 사람 수: 128
// 평균 시도: 2.49

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
  cin >> N;

  bool no_zero = true, no_natural = true;
  vector<int> passwords(N);
  for (int &password : passwords)
  {
    cin >> password;
    if (password != 0)
      no_natural = false;
    if (password == 0)
      no_zero = false;
  }

  sort(passwords.begin(), passwords.end());

  int tmp = 0;
  for (int password : passwords)
  {
    if (tmp == password)
      ++tmp;
    else if (tmp < password)
      break;
  }

  if (no_natural)
    cout << 0 << '\n';
  else if (no_zero)
    cout << 1 << '\n';
  else
    cout << tmp + 1 << '\n';

  for (int &password : passwords)
    cout << password << ' ';

  return 0;
}
