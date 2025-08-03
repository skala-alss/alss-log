// 검증수 (2475)
// https://www.acmicpc.net/problem/2475

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int result = 0;
    int N;
    for (int i = 1; i <= 5; ++i)
    {
        cin >> N;
        result += N * N;
    }

    cout << (result %= 10);

    return 0;
}
