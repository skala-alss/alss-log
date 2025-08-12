// 사분면 고르기 (14681)
// https://www.acmicpc.net/problem/14681

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int X, Y;
    cin >> X >> Y;

    if (X > 0 && Y > 0)
        cout << 1;
    if (X < 0 && Y > 0)
        cout << 2;
    if (X < 0 && Y < 0)
        cout << 3;
    if (X > 0 && Y < 0)
        cout << 4;

    return 0;
}
