// 약수 구하기 (2501)
// https://www.acmicpc.net/problem/2501

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;

    cin >> N >> K;
    int count = 0;

    for (int i = 1; i <= N; ++i)
    {
        if (N % i == 0)
            ++count;
        if (count == K)
        {
            cout << i;
            break;
        }
    }

    if (count < K)
        cout << 0;

    return 0;
}
