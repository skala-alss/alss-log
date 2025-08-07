// 윤년 (2753)
// https://www.acmicpc.net/problem/2753

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    cout << ((N % 4 == 0 && N % 100 != 0) | N % 400 == 0) ? 1 : 0;

    return 0;
}
