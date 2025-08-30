#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int grade;
    cin >> grade;
    if (grade >= 90 && grade <= 100){
        cout << 'A';
    }
    else if (grade >= 80 && grade < 90){
        cout << 'B';
    }
    else if (grade >= 70 && grade < 80){
        cout << 'C';
    }
    else if (grade >= 60 && grade < 70){
        cout << 'D';
    }
    else{
        cout << 'F';
    }

    return 0;
}