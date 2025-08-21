// 5622 – 다이얼
// https://www.acmicpc.net/problem/5622
// solved.ac: https://solved.ac/search?query=5622
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: 🟫 Bronze II
// 태그: 구현
// 푼 사람 수: 84,138
// 평균 시도: 1.71

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

  unordered_map<char, int> alphabet = {
      {'A', 3}, {'B', 3}, {'C', 3}, {'D', 4}, {'E', 4}, {'F', 4}, {'G', 5}, {'H', 5}, {'I', 5}, {'J', 6}, {'K', 6}, {'L', 6}, {'M', 7}, {'N', 7}, {'O', 7}, {'P', 8}, {'Q', 8}, {'R', 8}, {'S', 8}, {'T', 9}, {'U', 9}, {'V', 9}, {'W', 10}, {'X', 10}, {'Y', 10}, {'Z', 10}};

  string S;
  cin >> S;

  int result = 0;
  for (char l : S)
    result += alphabet[l];

  cout << result;
  return 0;
}
