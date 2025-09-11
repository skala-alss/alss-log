#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string grade;
    cin >> grade;

    double score = 0.0;
    if (grade == "A+") score = 4.3;
    else if (grade == "A0") score = 4.0;
    else if (grade == "A-") score = 3.7;
    else if (grade == "B+") score = 3.3;
    else if (grade == "B0") score = 3.0;
    else if (grade == "B-") score = 2.7;
    else if (grade == "C+") score = 2.3;
    else if (grade == "C0") score = 2.0;
    else if (grade == "C-") score = 1.7;
    else if (grade == "D+") score = 1.3;
    else if (grade == "D0") score = 1.0;
    else if (grade == "D-") score = 0.7;
    else if (grade == "F") score = 0.0;

    cout << fixed << setprecision(1) << score;

    return 0;
}