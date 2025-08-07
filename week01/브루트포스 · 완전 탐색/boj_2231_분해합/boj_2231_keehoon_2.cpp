// 분해합 (2231)
// https://www.acmicpc.net/problem/2231

#include <iostream>

using namespace std;

int digit_sum(int i)
{
    int sum = i;
    while (i)
    {
        sum += i % 10;
        i /= 10;
    }
    return sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int start = max(1, N - 9 * (int)to_string(N).length());
    for (int i = start; i < N; ++i)
        if (digit_sum(i) == N)
        {
            cout << i;
            return 0;
        }
    cout << 0;
    return 0;
}
