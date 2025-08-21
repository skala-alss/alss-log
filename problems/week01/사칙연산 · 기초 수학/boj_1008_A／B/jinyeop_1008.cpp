#include <iostream>
#include <iomanip> // 입력 / 출력 조작기 라이브러리

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double A, B;
    cin >> A >> B;
    cout << fixed << setprecision(10) << A / B;

    return 0;
}