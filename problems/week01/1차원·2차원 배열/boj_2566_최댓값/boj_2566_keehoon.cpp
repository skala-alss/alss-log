// 최댓값 (2566)
// https://www.acmicpc.net/problem/2566

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int max = -1;
    pair<int, int> coordinate;
    int current = 0;
    for (int i = 1; i <= 9; ++i)
        for (int j = 1; j <= 9; ++j)
        {
            cin >> current;
            if (max < current)
            {
                max = current;
                coordinate = {i, j};
            }
        }
    cout << max << '\n'
         << coordinate.first << ' ' << coordinate.second;

    return 0;
}
