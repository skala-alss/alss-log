// 7785 – 회사에 있는 사람
// https://www.acmicpc.net/problem/7785
// solved.ac: https://solved.ac/search?query=7785
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver V
// 태그: 자료 구조, 집합과 맵, 해시를 사용한 집합과 맵
// 푼 사람 수: 25,903
// 평균 시도: 2.42

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

  int n;
  cin >> n;
  set<string, greater<string>> s;

  while (n--)
  {
    string name, record;
    cin >> name >> record;

    if (record == "enter")
      s.insert(name);
    else if (record == "leave")
      s.erase(name);
  }

  for (string name : s)
    cout << name << '\n';
  return 0;
}
