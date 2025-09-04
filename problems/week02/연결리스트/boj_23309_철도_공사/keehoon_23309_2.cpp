// 23309 – 철도 공사
// https://www.acmicpc.net/problem/23309
// solved.ac: https://solved.ac/search?query=23309
// 시간 제한: 2 초 (추가 시간 없음)
// 메모리 제한: 512 MB (추가 메모리 없음)
// 티어: 🟡 Gold IV
// 태그: 구현, 연결 리스트, 자료 구조
// 푼 사람 수: 617
// 평균 시도: 4.56

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

  vector<int> route_map(N);

  for (int &station : route_map)
    cin >> station;

  vector<int> left(1e6 + 1), right(1e6 + 1);
  for (int i = 0; i < N; ++i)
  {
    int current = route_map[i];
    int previous = route_map[(i - 1 + N) % N];
    int next = route_map[(i + 1) % N];
    left[current] = previous;
    right[current] = next;
  }

  string output;
  output.reserve(M * 5);

  while (M--)
  {
    string code;
    cin >> code;

    if (code == "BN")
    {
      int i, j;
      cin >> i >> j;
      output += to_string(right[i]) + '\n';
      left[j] = i;
      right[j] = right[i];
      left[right[j]] = j;
      right[i] = j;
    }
    else if (code == "BP")
    {
      int i, j;
      cin >> i >> j;
      output += to_string(left[i]) + '\n';
      right[j] = i;
      left[j] = left[i];
      right[left[j]] = j;
      left[i] = j;
    }
    else if (code == "CN")
    {
      int i;
      cin >> i;
      int temp = right[i];
      output += to_string(temp) + '\n';
      right[i] = right[temp];
      left[right[i]] = i;
    }
    else if (code == "CP")
    {
      int i;
      cin >> i;
      int temp = left[i];
      output += to_string(temp) + '\n';
      left[i] = left[temp];
      right[left[i]] = i;
    }
  }

  cout << output;
  return 0;
}
