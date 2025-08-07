// 문자와 문자열 (27866)
// https://www.acmicpc.net/problem/27866

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    int i;
    cin >> S >> i;

    cout << S[i - 1];

    return 0;
}
