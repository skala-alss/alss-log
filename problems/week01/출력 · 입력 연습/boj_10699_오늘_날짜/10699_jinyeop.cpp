// 오늘 날짜 (10699)
// https://www.acmicpc.net/problem/10699

#include <iostream>
#include <iomanip>
#include <ctime>
// #include <windows.h>

using namespace std;

int main()
{
    // SetConsoleOutputCP(CP_UTF8);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 1. 현재 시간을 time_t 타입(1970년 1월 1일부터 초 단위)으로 가져오기
    time_t now = time(nullptr);

    // 2. time_t -> tm 구조체로 변환 (로컬 시간대로 변환)
    tm* localTime = localtime(&now);

    cout << put_time(localTime, "%Y-%m-%d");

    return 0;
}
