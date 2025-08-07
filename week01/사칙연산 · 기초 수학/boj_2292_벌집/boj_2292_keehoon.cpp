// 벌집 (2292)
// https://www.acmicpc.net/problem/2292

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int rooms = 1;
    int border = 0;

    while (N > max(border, 1))
    {
        N -= max(border, 1);
        ++rooms;
        border += 6;
    }
    cout << rooms;

    return 0;
}
