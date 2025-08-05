// 대소문자 바꾸기 (2744)
// https://www.acmicpc.net/problem/2744

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string word;
    cin >> word;

    for (char &c : word)
        // {
        //     if (islower(c))
        //         cout << char(toupper(c));
        //     else if (isupper(c))
        //         cout << char(tolower(c));
        // }
        c = isupper(c) ? tolower(c) : toupper(c);

    cout << word;

    return 0;
}
