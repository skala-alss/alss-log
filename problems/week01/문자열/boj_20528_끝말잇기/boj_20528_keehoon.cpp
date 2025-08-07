// 끝말잇기 (20528)
// https://www.acmicpc.net/problem/20528

#include <iostream>
#include <set>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    set<char> words;

    string palindrome;

    cin >> N;
    while (N--)
    {
        cin >> palindrome;
        words.insert(palindrome.front());
    }

    cout << (words.size() == 1 ? 1 : 0);

    return 0;
}
