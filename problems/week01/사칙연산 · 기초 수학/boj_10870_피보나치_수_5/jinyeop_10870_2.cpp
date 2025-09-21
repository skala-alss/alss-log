#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, a[100];
    a[0] = 0;
    a[1] = 1;
    cin >> n;
    
    for (int i = 2; i <= n; ++i) {
        a[i] = a[i - 2] + a[i - 1];
    }
    
    cout << a[n];
    
    return 0;
}