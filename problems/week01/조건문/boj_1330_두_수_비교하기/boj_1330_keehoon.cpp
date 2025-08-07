// 두 수 비교하기 (1330)
// https://www.acmicpc.net/problem/1330

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B;
    cin >> A >> B;

    if (A > B)
        cout << '>';
    if (A < B)
        cout << '<';
    if (A == B)
        cout << "==";

    return 0;
}
