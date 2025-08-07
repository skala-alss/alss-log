// 최소공배수 (1934)
// https://www.acmicpc.net/problem/1934

#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, A, B;
    cin >> T;
    while (T--)
    {
        cin >> A >> B;
        cout << A * B / gcd(max(A, B), min(A, B)) << '\n';
    }
    return 0;
}
