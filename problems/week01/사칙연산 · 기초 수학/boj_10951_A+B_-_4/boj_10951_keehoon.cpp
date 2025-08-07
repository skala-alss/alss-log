// A+B - 4 (10951)
// https://www.acmicpc.net/problem/10951

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B;

    while (cin >> A)
    {
        cin >> B;
        cout << A + B << '\n';
    }

    return 0;
}
