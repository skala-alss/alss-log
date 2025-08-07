// 문자열 (9086)
// https://www.acmicpc.net/problem/9086

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    string S;

    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        cin >> S;
        cout << *S.begin() << *(S.end() - 1) << '\n';
    }

    return 0;
}
