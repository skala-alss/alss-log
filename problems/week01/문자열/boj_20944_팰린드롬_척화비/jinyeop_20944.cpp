#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cout << 'a';
    }
    cout <<'\n';
    
    return 0;
}

/** 11~13줄 :
 * while (N--) // 0이 되면 반복문 종료
 *  cout << 'a';
 */