// 사칙연산 (10869)
// https://www.acmicpc.net/problem/10869

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B;
    cin >> A >> B;
    cout << A + B << '\n';
    cout << A - B << '\n';
    cout << A * B << '\n';
    cout << A / B << '\n';
    cout << A % B << '\n';
    return 0;
}
