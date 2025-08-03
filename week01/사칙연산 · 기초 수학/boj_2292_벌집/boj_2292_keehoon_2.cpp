// 벌집 (2292)
// https://www.acmicpc.net/problem/2292

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double N;
    cin >> N;

    cout << ceil((1 + sqrt(((4 * (N - 1)) / 3) + 1)) / 2);

    return 0;
}
