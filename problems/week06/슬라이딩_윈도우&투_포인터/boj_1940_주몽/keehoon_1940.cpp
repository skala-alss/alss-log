// 1940 – 주몽
// https://www.acmicpc.net/problem/1940
// solved.ac: https://solved.ac/search?query=1940
// 시간 제한: 2 초
// 메모리 제한: 128 MB
// 티어: ⚪ Silver IV
// 태그: 두 포인터, 정렬
// 푼 사람 수: 15,260
// 평균 시도: 2.11

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

  int N, M;
  cin >> N >> M;
  vector<int> ingredients(N);
  for (int &ingredient : ingredients)
    cin >> ingredient;
  sort(ingredients.begin(), ingredients.end());

  int l = 0, r = N - 1;
  int armors = 0;
  while (l < r)
  {
    int sum = ingredients[l] + ingredients[r];
    if (sum == M)
    {
      ++armors;
      ++l;
      --r;
    }

    else if (sum < M)
      ++l;

    else if (sum > M)
      --r;
  }

  cout << armors;

  return 0;
}
