// 벌집 (2292)
// https://www.acmicpc.net/problem/2292

#include <iostream>
using namespace std;

bool enough(int n, int target)
{
    return 3LL * n * (n - 1) + 1 >= target;
}

int main()
{
    int N;
    cin >> N;

    int lo = 1, hi = 2e5, res = 1;
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        if (enough(mid, N))
        {
            res = mid;
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }

    cout << res << '\n';
}
