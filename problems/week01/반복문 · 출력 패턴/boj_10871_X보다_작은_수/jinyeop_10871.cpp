#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, X, A;
    cin >> N >> X;
    
    int i = 0;
    while (i < N) {
        cin >> A;
        if (A < X) cout << A << " ";
        ++i;
    }
    
    return 0;
}