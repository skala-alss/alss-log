// 블랙잭 (2798)
// https://www.acmicpc.net/problem/2798

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> cards(N);
    for (int &card : cards)
        cin >> card;

    int max_val = 0;
    for (int i = 0; i < N - 2; ++i)
        for (int j = i + 1; j < N - 1; ++j)
            for (int k = j + 1; k < N; ++k)
                if (max_val < cards[i] + cards[j] + cards[k] && cards[i] + cards[j] + cards[k] <= M)
                    max_val = cards[i] + cards[j] + cards[k];

    cout << max_val;

    return 0;
}
