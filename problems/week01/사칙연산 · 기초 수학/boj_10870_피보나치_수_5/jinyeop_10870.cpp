#include <iostream>
using namespace std;

int fibonacci(int n){
    int result;
    if(n == 0) result = 0;
    if(n == 1) result = 1;
    if(n >= 2) result = fibonacci(n - 2) + fibonacci(n - 1);
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    cout << fibonacci(n);
    
    return 0;
}