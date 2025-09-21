#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    
    int step = 1;
    int max_in_layer = 1;
    
    while (N > max_in_layer) {
        max_in_layer += 6 * step;
        step++;
    }
    cout << step;
    return 0;
}