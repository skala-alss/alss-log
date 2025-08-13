// 10828 – 스택
// https://www.acmicpc.net/problem/10828
// solved.ac: https://solved.ac/search?query=10828
// 시간 제한: 0.5 초 (추가 시간 없음)
// 메모리 제한: 256 MB
// 티어: ⚪ Silver IV
// 태그: 구현, 스택, 자료 구조
// 푼 사람 수: 84,114
// 평균 시도: 2.58

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
