// A+B - 3 (10950)
// https://www.acmicpc.net/problem/10950

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, A, B;
    cin >> T;
    for (int i = 1; i <= T; ++i)
    {
        cin >> A >> B;
        cout << A + B << '\n';
    }

    return 0;
}
