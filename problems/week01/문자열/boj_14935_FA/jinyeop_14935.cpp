#include <iostream>
#include <string>
using namespace std;

string Fx(string n) {
    int first_degit = n[0] - '0';
    int length = n.length();
    int result = first_degit * length;
    return to_string(result);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string x;
    cin >> x;
    
    while (x.length() > 1) {
        x = Fx(x);
    }
    cout << "FA\n";
    
    return 0;
}