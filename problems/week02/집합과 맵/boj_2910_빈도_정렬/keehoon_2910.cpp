// 2910 – 빈도 정렬
// https://www.acmicpc.net/problem/2910
// solved.ac: https://solved.ac/search?query=2910
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver III
// 태그: 자료 구조, 정렬, 집합과 맵, 해시를 사용한 집합과 맵
// 푼 사람 수: 6,791
// 평균 시도: 1.77

#include <algorithm>
#include <iostream>
#include <unordered_map>
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

  int N, C;
  cin >> N >> C;

  unordered_map<int, pair<int, int>> freq;

  for (int i = 1; i <= N; ++i)
  {
    int msg;
    cin >> msg;
    if (!freq.count(msg))
      freq[msg] = make_pair(0, i);
    ++freq[msg].first;
  }

  vector<tuple<int, int, int>> arr;
  for (auto &kv : freq)
    arr.push_back(make_tuple(kv.first, kv.second.first, kv.second.second));

  sort(arr.begin(), arr.end(), [](auto &a, auto &b)
       { if (get<1>(a) != get<1>(b)) return get<1>(a) > get<1>(b);
             return get<2>(a) < get<2>(b); });

  for (auto &t : arr)
    for (int i = 1; i <= get<1>(t); ++i)
      cout << get<0>(t) << ' ';
  return 0;
}
