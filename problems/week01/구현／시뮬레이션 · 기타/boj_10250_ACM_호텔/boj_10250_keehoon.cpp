#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, H, W, N;
    cin >> T;

    while (T--)
    {
        cin >> H >> W >> N;
        int floor = (N - 1) % H + 1;
        int room = (N - 1) / H + 1;
        cout << floor << setfill('0') << setw(2) << room << '\n';
    }

    return 0;
}
