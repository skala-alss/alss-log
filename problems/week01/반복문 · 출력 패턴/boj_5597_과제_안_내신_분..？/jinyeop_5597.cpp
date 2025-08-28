#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int arr[31] = {};
    
    for (int i = 0; i < 28; ++i) {
        int n;
        cin >> n;
        arr[n] = 1;
    }
    
    for (int k = 1; k <= 30; ++k) {
        if (arr[k] == 0) {
            cout << k << '\n';
        }
    }
    
    return 0;
}