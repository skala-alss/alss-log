// 2565 – 전깃줄
// https://www.acmicpc.net/problem/2565
// solved.ac: https://solved.ac/search?query=2565
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: 🟡 Gold V
// 태그: 다이나믹 프로그래밍
// 푼 사람 수: 19,006
// 평균 시도: 2.05

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

  struct Wire
  {
    int A, B;

    Wire() : A(0), B(0) {}
    Wire(int A, int B) : A(A), B(B) {}

    bool operator<(const Wire other) const
    {

      if (A == other.A)
        return B < other.B;
      return A < other.A;
    }
  };

  int N;
  cin >> N;

  vector<Wire> wires(N);
  for (Wire &wire : wires)
    cin >> wire.A >> wire.B;

  sort(wires.begin(), wires.end());

  vector<vector<int>> in_degrees(2, vector<int>(N, 1));
  for (int i = 0; i < N; ++i)
    in_degrees[0][i] = wires[i].B;

  for (int i = 1; i < N; ++i)
    for (int j = 0; j < i; ++j)
      if (in_degrees[0][i] > in_degrees[0][j])
        in_degrees[1][i] = max(in_degrees[1][i], in_degrees[1][j] + 1);

  cout << N - *max_element(in_degrees[1].begin(), in_degrees[1].end());

  return 0;
}
