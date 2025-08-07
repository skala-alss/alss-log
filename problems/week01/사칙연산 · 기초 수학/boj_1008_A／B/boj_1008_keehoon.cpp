// A/B (1008)
// https://www.acmicpc.net/problem/1008

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double A, B;
    cin >> A >> B;
    cout << fixed;
    cout.precision(9);
    cout << A / B;
    return 0;
}
