// Gemini를 통한 추가적인 코드 학습
#include <iostream>   // 표준 입출력을 위한 헤더
#include <vector>     // 동적 배열인 std::vector를 사용하기 위한 헤더
#include <numeric>    // std::accumulate와 같은 수치 연산 함수를 위한 헤더

// main 함수
int main() {
    // C++ 표준 스트림과 C 표준 스트림의 동기화를 해제하여 입출력 속도를 높입니다.
    // 대규모 입출력 시 성능 향상에 도움을 줍니다.
    std::ios::sync_with_stdio(false);
    
    // std::cin과 std::cout의 연결을 끊어줍니다.
    // 이 역시 입력 성능을 향상시키는 역할을 합니다.
    std::cin.tie(nullptr);

    // int형 원소 5개를 저장할 수 있는 std::vector를 선언하고 초기화합니다.
    // 'vector'는 크기가 가변적인 동적 배열입니다.
    std::vector<int> nums(5);
    
    // for 반복문을 사용하여 5개의 정수를 nums 벡터에 입력받습니다.
    for (int i = 0; i < 5; ++i) {
        std::cin >> nums[i];
    }
    
    // std::accumulate 함수를 사용하여 nums 벡터 원소들의 제곱의 합을 구합니다.
    int sum_of_squares = std::accumulate(
        nums.begin(), // 1. 누적 연산을 시작할 첫 번째 위치 (iterator)
        nums.end(),   // 2. 누적 연산을 마칠 마지막 위치 (end iterator)
        0,            // 3. 초기 합계 값. 이 문제에서는 0부터 시작합니다.
        
        // 4. 연산 로직을 정의하는 '람다 함수(Lambda Function)'
        // [](int total, int n) { ... }는 이름이 없는 익명 함수를 정의합니다.
        // - 'total'은 현재까지의 누적값 (초기값 0에서 시작)
        // - 'n'은 nums 벡터의 각 원소 (1개씩 순서대로 들어옴)
        // - 'return total + n * n;'은 현재 누적값에 원소의 제곱을 더한 값을 반환합니다.
        //   이 반환값은 다음 순서의 total 값이 됩니다.
        [](int total, int n) {
            return total + n * n;
        }
    );
    
    // 최종 결과인 'sum_of_squares'를 10으로 나눈 나머지 값을 출력합니다.
    std::cout << sum_of_squares % 10;

    return 0;
}