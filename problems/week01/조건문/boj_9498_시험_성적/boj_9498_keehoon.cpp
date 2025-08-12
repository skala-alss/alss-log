// 시험 성적 (9498)
// https://www.acmicpc.net/problem/9498

#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    switch (N / 10)
    {
    case 10:
    case 9:
        cout << 'A';
        break;
    case 8:
        cout << 'B';
        break;
    case 7:
        cout << 'C';
        break;
    case 6:
        cout << 'D';
        break;

    default:
        cout << 'F';
        break;
    }

    // if (90 <= N && N <= 100)
    //     cout << 'A';
    // else if (80 <= N && N <= 89)
    //     cout << 'B';
    // else if (70 <= N && N <= 79)
    //     cout << 'C';
    // else if (60 <= N && N <= 69)
    //     cout << 'D';
    // else
    //     cout << 'F';

    return 0;
}
