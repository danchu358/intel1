#include <iostream>

template <typename T>
T findMax(const T arr[], int size) {
    if (size <= 0) {
        std::cerr << "Array size should be greater than 0." << std::endl;
        exit(1);
    }

    T maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

int main() {
    int intArray[] = { 3, 8, 1, 9, 4, 6 };
    int intArraySize = sizeof(intArray) / sizeof(intArray[0]);
    int maxInt = findMax(intArray, intArraySize);
    std::cout << "Maximum value in the integer array: " << maxInt << std::endl;

    double doubleArray[] = { 2.5, 7.8, 1.1, 9.2, 5.4 };
    int doubleArraySize = sizeof(doubleArray) / sizeof(doubleArray[0]);
    double maxDouble = findMax(doubleArray, doubleArraySize);
    std::cout << "Maximum value in the double array: " << maxDouble << std::endl;

    return 0;
}