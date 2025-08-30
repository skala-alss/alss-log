#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, y;
    cin >> x;
    cin >> y;
    if(x > 0 && y > 0){
        cout << 1;
    }
    else if(x < 0 && y > 0){
        cout << 2;
    }
    else if(x < 0 && y < 0){
        cout << 3;
    }
    else if(x > 0 && y < 0){
        cout << 4;
    }
    return 0;
}