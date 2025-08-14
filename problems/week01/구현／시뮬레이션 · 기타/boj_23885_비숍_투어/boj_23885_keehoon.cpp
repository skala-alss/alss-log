// 비숍 투어 (23885)
// https://www.acmicpc.net/problem/23885

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, sx, sy, ex, ey;
    cin >> N >> M >> sx >> sy >> ex >> ey;

    cout << ((((sx + sy) % 2 == (ex + ey) % 2 && N && (N != 1 && M != 1)) || (sx == ex && sy == ey)) ? "YES" : "NO");

    // bool same_cell = (sx == ex && sy == ey);
    // bool same_color = (sx + sy) % 2 == (ex + ey) % 2;
    // bool board_valid = N > 1 && M > 1;

    // cout << ((same_cell || (same_color && board_valid)) ? "YES" : "NO") << '\n';

    return 0;
}