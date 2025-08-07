// 구구단 (2739)
// https://www.acmicpc.net/problem/2739

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= 9; ++i)
        cout << N << " * " << i << " = " << N * i << '\n';

    return 0;
}
