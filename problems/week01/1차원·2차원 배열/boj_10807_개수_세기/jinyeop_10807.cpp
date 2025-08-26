#include <iostream>

using namespace std;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, v;
    cin >> N;
    int* arr = new int[N]; // N 크기만큼 정수 배열 동적 할당
    
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }
    cin >> v;
    int count = 0;
    for (int k = 0; k < N; ++k) {
        if(arr[k] == v)
            count++;
    }
    cout << count;
    
    delete[] arr;
    return 0;
}