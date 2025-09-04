// 5430 – AC
// https://www.acmicpc.net/problem/5430
// solved.ac: https://solved.ac/search?query=5430
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: 🟡 Gold V
// 태그: 구현, 덱, 문자열, 자료 구조, 파싱
// 푼 사람 수: 30,689
// 평균 시도: 4.75

#include <algorithm>
#include <iostream>
#include <deque>
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

  int T;
  cin >> T;

  deque<int> arr;
  while (T--)
  {
    string p, numbers;
    int n;

    cin >> p >> n >> numbers;

    arr.clear();
    string number;
    for (char c : numbers)
      if (isdigit(c))
        number += c;
      else if (!number.empty())
      {
        arr.push_back(stoi(number));
        number.clear();
      }

    bool straight = true;
    bool valid = true;
    for (char func : p)
    {
      if (func == 'R')
        straight = !straight;

      else if (func == 'D' && !arr.empty())
        straight ? arr.pop_front() : arr.pop_back();

      else
      {
        valid = false;
        cout << "error" << '\n';
        break;
      }
    }

    if (!straight)
      reverse(arr.begin(), arr.end());

    if (valid)
    {
      cout << '[';
      for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << (i < arr.size() - 1 ? "," : "");
      cout << ']' << '\n';
    }
  }
  return 0;
}
