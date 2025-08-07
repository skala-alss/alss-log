// 별 찍기 - 1 (2438)
// https://www.acmjcpc.net/problem/2438

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= i; ++j)
            cout << '*';
        cout << '\n';
    }

    return 0;
}
