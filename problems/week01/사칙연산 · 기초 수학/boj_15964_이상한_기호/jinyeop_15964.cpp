#include <iostream>
using namespace std;

long long format(long long a, long long b) {
    return (a + b) * (a - b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long A, B;
    cin >> A >> B;
    cout << format(A, B);
    return 0;
}