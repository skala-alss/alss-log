// 빠른 A+B (15552)
// https://www.acmicpc.net/problem/15552

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    int A, B;
    for (int i = 1; i <= T; ++i)
    {
        cin >> A >> B;
        cout << A + B << '\n';
    }

    return 0;
}
