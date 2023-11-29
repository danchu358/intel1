#include <iostream>

template <typename T>
T findMax(const T arr[], int size) {
    if (size <= 0) {
        std::cerr << "Array size should be greater than 0." << std::endl;
        exit(1);
    }

    T maxVal = arr[0]; // 초기값으로 배열의 첫 번째 요소를 선택
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i]; // 더 큰 값을 발견하면 최대값을 업데이트
        }
    }
    return maxVal;
}

int main() {
    // 정수 배열에서 최대값 찾기
    int intArray[] = { 3, 8, 1, 9, 4, 6 };
    int intArraySize = sizeof(intArray) / sizeof(intArray[0]);
    int maxInt = findMax(intArray, intArraySize);
    std::cout << "Maximum value in the integer array: " << maxInt << std::endl;

    // 실수 배열에서 최대값 찾기
    double doubleArray[] = { 2.5, 7.8, 1.1, 9.2, 5.4 };
    int doubleArraySize = sizeof(doubleArray) / sizeof(doubleArray[0]);
    double maxDouble = findMax(doubleArray, doubleArraySize);
    std::cout << "Maximum value in the double array: " << maxDouble << std::endl;

    return 0;
}