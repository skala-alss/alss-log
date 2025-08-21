// 20291 – 파일 정리
// https://www.acmicpc.net/problem/20291
// solved.ac: https://solved.ac/search?query=20291
// 시간 제한: 3 초 (추가 시간 없음)
// 메모리 제한: 1024 MB
// 티어: ⚪ Silver III
// 태그: 문자열, 자료 구조, 정렬, 집합과 맵, 트리를 사용한 집합과 맵, 파싱, 해시를 사용한 집합과 맵
// 푼 사람 수: 6,101
// 평균 시도: 1.45

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

  map<string, int> extensions;

  while (N--)
  {
    string file;
    cin >> file;

    int n = file.length();
    auto it = file.find('.');

    ++extensions[file.substr(it + 1)];
  }

  for (auto &kv : extensions)
    cout << kv.first << ' ' << kv.second << '\n';
  return 0;
}
