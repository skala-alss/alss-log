// 17219 – 비밀번호 찾기
// https://www.acmicpc.net/problem/17219
// solved.ac: https://solved.ac/search?query=17219
// 시간 제한: 5 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver IV
// 태그: 자료 구조, 집합과 맵, 해시를 사용한 집합과 맵
// 푼 사람 수: 21,659
// 평균 시도: 1.39

#include <iostream>
#include <unordered_map>
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

  unordered_map<string, string> pws;
  pws.reserve(N * 2);

  while (N--)
  {
    string domain, pw;
    cin >> domain >> pw;
    pws.insert(make_pair(domain, pw));
  }

  while (M--)
  {
    string domain;
    cin >> domain;
    cout << pws[domain] << '\n';
  }
  return 0;
}
