#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(1){
        int A, B;
        cin >> A >> B;
        if( A == 0 && B == 0) break;
        cout << A + B << '\n';
    }

    return 0;
}