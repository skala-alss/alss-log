// 2447 – 별 찍기 - 10
// https://www.acmicpc.net/problem/2447
// solved.ac: https://solved.ac/search?query=2447
// 시간 제한: 1 초
// 메모리 제한: 256 MB
// 티어: 🟡 Gold V
// 태그: 분할 정복, 재귀
// 푼 사람 수: 37,427
// 평균 시도: 1.76

#include <iostream>
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
    if (_isatty(_fileno(stdin))) { freopen("input.txt", "r", stdin); }
#else
    if (isatty(fileno(stdin))) { freopen("input.txt", "r", stdin); }
#endif

    int N, M;
    if (!(cin >> N >> M)) return 0;
    cout << "N: " << N << " M: " << M << "\n";
    return 0;
}
