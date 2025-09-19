#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b, c;
    cin >> a >> b >> c;
    int result;
    
    if (a == b && b == c) result = 10000 + a * 1000;
    else if (a == b || b == c || a == c) {
        if (a == b) {
            result = 1000 + a * 100;
        }
        else if (b == c) {
            result = 1000 + b * 100;
        }
        else {
            result = 1000 + c * 100;
        }
    } else {
        int max_value = max(a, max(b, c));
        result = max_value * 100;
    }
    
    cout << result;
    return 0;
}