#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    int i = 0;
    while (i < T) {
        string str;
        cin >> str;
        cout << str[0] << str[str.length() - 1] << '\n';
        ++i;
    }
    return 0;
}