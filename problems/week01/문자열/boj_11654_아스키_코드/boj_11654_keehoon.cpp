// 아스키 코드 (11654)
// https://www.acmicpc.net/problem/11654

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char N;
    cin >> N;

    cout << N - '\0';

    return 0;
}
