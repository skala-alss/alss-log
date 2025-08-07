// X보다 작은 수 (10871)
// https://www.acmicpc.net/problem/10871

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, X, C;
    cin >> N >> X;

    while (cin >> C)
        if (X > C)
            cout << C << ' ';
    return 0;
}
