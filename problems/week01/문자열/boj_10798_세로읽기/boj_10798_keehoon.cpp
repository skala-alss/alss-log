// 세로읽기 (10798)
// https://www.acmicpc.net/problem/10798

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> words(5);
    for (string &word : words)
        cin >> word;

    for (int i = 0; i < 15; ++i)
        for (string &word : words)
            if (i < word.length())
                cout << word[i];

    return 0;
}
