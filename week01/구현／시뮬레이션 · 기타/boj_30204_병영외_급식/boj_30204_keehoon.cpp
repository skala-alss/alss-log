// 병영외 급식 (30204)
// https://www.acmicpc.net/problem/30204

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, X;
    cin >> N >> X;

    vector<int> dormitories(N);
    for (int &dormitory : dormitories)
        cin >> dormitory;

    cout << (accumulate(dormitories.begin(), dormitories.end(), 0) % X ? 0 : 1);

    return 0;
}
