// 과제 안 내신 분..? (5597)
// https://www.acmicpc.net/problem/5597

#include <iostream>

using namespace std;

bool students[31];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num = 0;
    for (int i = 0; i < 28; students[num] = true, ++i)
        cin >> num;

    for (int i = 1; i <= 30; ++i)
        if (!students[i])
            cout << i << '\n';

    return 0;
}
