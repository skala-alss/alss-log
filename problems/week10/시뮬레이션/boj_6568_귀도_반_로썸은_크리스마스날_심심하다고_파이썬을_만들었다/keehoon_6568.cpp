// 6568 – 귀도 반 로썸은 크리스마스날 심심하다고 파이썬을 만들었다
// https://www.acmicpc.net/problem/6568
// solved.ac: https://solved.ac/search?query=6568
// 시간 제한: 1 초
// 메모리 제한: 128 MB
// 티어: 🟡 Gold V
// 태그: 구현, 시뮬레이션
// 푼 사람 수: 350
// 평균 시도: 4.66

#include <bitset>
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

  while (true)
  {
    unsigned char adder = 0, pc = 0;
    vector<string> pids(1 << 5);

    for (int i = 0; i < 1 << 5; ++i)
      if (!(cin >> pids[i]))
        return 0;

    while (true)
    {
      string cmd_bits = pids[pc].substr(0, 3), val_bits = pids[pc].substr(3, 5);

      int command = stoi(cmd_bits, nullptr, 2), value = stoi(val_bits, nullptr, 2);

      pc = pc + 1 & 31;

      switch (command)
      {
      case 0:
        pids[value] = bitset<8>(adder).to_string();
        break;
      case 1:
        adder = stoi(pids[value], nullptr, 2);
        break;
      case 2:
        if (adder == 0)
          pc = value;
        break;
      case 3:
        break;
      case 4:
        --adder;
        break;
      case 5:
        ++adder;
        break;
      case 6:
        pc = value;
        break;
      case 7:
        cout << bitset<8>(adder) << '\n';
        goto next_case;
      }
    }
  next_case:;
  }
}
