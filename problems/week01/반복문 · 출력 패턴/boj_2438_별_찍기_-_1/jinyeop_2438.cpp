#include <iostream>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    for(int k = 1; k <= N; ++k) {
        for(int i = 1; i <= k; ++i) { // 이중 for 문 구현 시에 조심할 것
            cout << "*";
        }
        cout << '\n';
    }
    return 0;
}