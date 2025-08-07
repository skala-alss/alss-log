// 행렬 덧셈 (2738)
// https://www.acmicpc.net/problem/2738

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> matrix_a(N, vector<int>(M));

    for (vector<int> &row : matrix_a)
        for (int &cell : row)
            cin >> cell;

    int C;
    for (int r = 0; r < N; ++r)
    {
        for (int c = 0; c < M; ++c)
        {
            cin >> C;
            cout << matrix_a[r][c] + C << ' ';
        }
        cout << '\n';
    }

    return 0;
}
