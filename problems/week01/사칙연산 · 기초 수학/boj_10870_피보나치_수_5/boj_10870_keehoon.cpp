// 피보나치 수 5 (10870)
// https://www.acmicpc.net/problem/10870

#include <iostream>

using namespace std;

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    cout << fib(N);
    return 0;
}
