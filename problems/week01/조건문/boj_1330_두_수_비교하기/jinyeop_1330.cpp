#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int A, B;
    cin >> A >> B;
    if (A > B){
        cout << ">";
    }
    else if (A < B){
        cout << "<";
    }
    else{
        cout << "==";
    }

    return 0;
}