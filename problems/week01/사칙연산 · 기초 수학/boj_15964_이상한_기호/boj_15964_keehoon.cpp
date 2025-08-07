// 이상한 기호 (15964)
// https://www.acmicpc.net/problem/15964

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long A, B;
    cin >> A >> B;
    cout << (A + B) * (A - B);

    return 0;
}
