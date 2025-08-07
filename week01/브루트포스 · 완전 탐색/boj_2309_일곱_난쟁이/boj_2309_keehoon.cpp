// 일곱 난쟁이 (2309)
// https://www.acmicpc.net/problem/2309

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> dwarfs(9);
    for (int &dwarf : dwarfs)
        cin >> dwarf;

    int two = accumulate(dwarfs.begin(), dwarfs.end(), 0) - 100;

    sort(dwarfs.begin(), dwarfs.end());
    for (int i = 0; i < 8; ++i)
        for (int j = i + 1; j < 9; ++j)
            if (dwarfs[i] + dwarfs[j] == two)
            {
                for (int k = 0; k < 9; ++k)
                    if (k != i && k != j)
                        cout << dwarfs[k] << '\n';
                return 0;
            }

    return 0;
}
