#include <iostream>
using namespace std;

int square(int n) {
    return n * n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int verifyNum;
    int sum = 0;
    
    for (int i = 0; i < 5; ++i) {
        int num;
        cin >> num;
        sum += square(num);
    }
    
    verifyNum = sum % 10;
    cout << verifyNum;
    return 0;
}