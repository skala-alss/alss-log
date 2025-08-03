// A+B - 5 (10952)
// https://www.acmicpc.net/problem/10952

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B;

    while (true)
    {
        cin >> A >> B;
        if (A + B)
            cout << A + B << '\n';
        else
            break;
    }

    return 0;
}
