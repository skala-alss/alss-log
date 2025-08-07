// 학점계산 (2754)
// https://www.acmicpc.net/problem/2754

#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    unordered_map<string, float> grade = {
        {"A+", 4.3}, {"A0", 4.0}, {"A-", 3.7}, {"B+", 3.3}, {"B0", 3.0}, {"B-", 2.7}, {"C+", 2.3}, {"C0", 2.0}, {"C-", 1.7}, {"D+", 1.3}, {"D0", 1.0}, {"D-", 0.7}, {"F", 0.0}};
    cin >> S;

    cout.precision(1);
    cout << fixed << grade[S];

    return 0;
}
