// 수학은 비대면강의입니다 (19532)
// https://www.acmicpc.net/problem/19532

#include <iostream>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    int x, y;

    // 크래머의 공식 기반 풀이
    int det = (a * e - b * d) ? a * e - b * d : b * d - a * e;

    x = (c * e - b * f) / det;
    y = (a * f - c * d) / det;

    cout << x << ' ' << y << '\n';
    return 0;
}
