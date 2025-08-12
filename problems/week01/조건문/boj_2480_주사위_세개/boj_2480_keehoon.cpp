// 주사위 세개 (2480)
// https://www.acmicpc.net/problem/2480

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B, C;
    cin >> A >> B >> C;

    if (A == B && B == C)
        cout << 10'000 + A * 1'000;
    else if (A == B | B == C | C == A)
    {
        int same = (A == B | A == C) ? A : B;
        cout << 1'000 + same * 100;
    }
    else
        cout << max({A, B, C}) * 100;

    return 0;
}
