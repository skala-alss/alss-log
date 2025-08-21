// 스물셋 (23251)
// https://www.acmicpc.net/problem/23251

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, k;
    cin >> T;
    while (T--)
    {
        cin >> k;
        cout << k * 23 << '\n';
    }

    return 0;
}
