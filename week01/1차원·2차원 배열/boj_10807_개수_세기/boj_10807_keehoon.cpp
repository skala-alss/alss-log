// 개수 세기 (10807)
// https://www.acmicpc.net/problem/10807

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, v;
    cin >> N;

    int ints[N] = {};

    for (int i = 0; i < N; ++i)
        cin >> ints[i];

    cin >> v;
    int count = 0;
    for (int i = 0; i < N; ++i)
        if (ints[i] == v)
            ++count;

    cout << count;

    return 0;
}
