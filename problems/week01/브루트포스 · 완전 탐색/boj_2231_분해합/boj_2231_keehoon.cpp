// 분해합 (2231)
// https://www.acmicpc.net/problem/2231

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = max(0, N - ((int)to_string(N).length() * 9)); i < N; ++i)
    {
        int decomposition = i;
        for (char &digit : to_string(i))
            decomposition += int(digit) - '0';

        if (decomposition == N)
        {
            cout << i;
            return 0;
        }
    }

    cout << 0;

    return 0;
}
