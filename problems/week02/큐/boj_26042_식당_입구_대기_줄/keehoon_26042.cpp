// 26042 – 식당 입구 대기 줄
// https://www.acmicpc.net/problem/26042
// solved.ac: https://solved.ac/search?query=26042
// 시간 제한: 0.1 초
// 메모리 제한: 512 MB
// 티어: ⚪ Silver V
// 태그: 구현, 자료 구조, 큐
// 푼 사람 수: 913
// 평균 시도: 3.08

#include <iostream>
#include <queue>
#if defined(_WIN32)
#include <io.h>
#include <cstdio>
#else
#include <unistd.h>
#include <cstdio>
#endif

using namespace std;

struct MaxQueue
{
  int students = 0;
  int last = 0;

  bool operator<(const MaxQueue &other) const
  {
    if (students != other.students)
      return students < other.students;
    return last > other.last;
  }
};

main()
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

  int n;
  MaxQueue result;
  queue<int> q;

  cin >> n;

  int info, student, last;
  while (n--)
  {
    cin >> info;
    if (info == 1)
    {
      cin >> student;
      last = student;
      q.push(student);
    }

    else if (info == 2)
      q.pop();

    MaxQueue current;
    current.students = q.size();
    current.last = last;

    result = max(result, current);
  }

  cout << result.students << ' ' << result.last;

  return 0;
}
