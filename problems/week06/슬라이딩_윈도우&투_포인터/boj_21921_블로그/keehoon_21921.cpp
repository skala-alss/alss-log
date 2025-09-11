// 21921 – 블로그
// https://www.acmicpc.net/problem/21921
// solved.ac: https://solved.ac/search?query=21921
// 시간 제한: 1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver III
// 태그: 누적 합, 슬라이딩 윈도우
// 푼 사람 수: 7,149
// 평균 시도: 2.36

#include <algorithm>
#include <iostream>
#include <vector>
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

  int N, X;
  cin >> N >> X;
  vector<int> visitants(N);
  for (int &visitant : visitants)
    cin >> visitant;
  unordered_map<int, int> counter;
  counter.reserve(25e4);

  int window = 0;
  for (int i = 0; i < N; ++i)
  {
    window += i >= X ? visitants[i] - visitants[i - X] : visitants[i];
    i >= X - 1 && ++counter[window];
  }

  auto it = max_element(counter.begin(), counter.end());
  if (it->first)
    cout << it->first << '\n'
         << it->second;
  else
    cout << "SAD";

  return 0;
}
