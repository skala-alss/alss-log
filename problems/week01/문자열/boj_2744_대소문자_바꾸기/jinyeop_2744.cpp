#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string word;
    cin >> word;

    for (char& c : word) {
        if (islower(c)) {
            c = toupper(c);
        } else if (isupper(c)) {
            c = tolower(c);
        }
        // c = isupper(c) ? tolower(c) : toupper(c); // 삼항연산자
    }

    cout << word;

    return 0;
}