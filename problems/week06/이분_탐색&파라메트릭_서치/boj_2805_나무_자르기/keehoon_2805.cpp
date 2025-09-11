// 2805 – 나무 자르기
// https://www.acmicpc.net/problem/2805
// solved.ac: https://solved.ac/search?query=2805
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: ⚪ Silver II
// 태그: 매개 변수 탐색, 이분 탐색
// 푼 사람 수: 47,767
// 평균 시도: 3.69

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
  vector<int> trees(N);
  for (int &tree : trees)
    cin >> tree;

  int result = 0;
  int l = 0;
  int r = *max_element(trees.begin(), trees.end());
  while (l <= r)
  {
    int mid = (l + r) / 2;
    long long len = 0;
    for (int &tree : trees)
      len += max(tree - mid, 0);

    if (len >= M)
    {
      result = max(result, mid);
      l = mid + 1;
    }

    else if (len < M)
      r = mid - 1;
  }

  cout << result;

  return 0;
}
