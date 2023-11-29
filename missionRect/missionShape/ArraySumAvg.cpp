#include <iostream>
using namespace std;

class SumAndAverage {
private:
    int sum;
    double average;

public:
    SumAndAverage() : sum(0), average(0) {}

    void calculateSumAndAverage(const int* arr, int size);
    int getSum() const { return sum; }
    double getAverage() const { return average; }
};

void SumAndAverage::calculateSumAndAverage(const int* arr, int size) {
    if (size == 0) {
        sum = 0;
        average = 0;
        return;
    }

    sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    average = static_cast<double>(sum) / size;
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5 };
    int size = sizeof(arr) / sizeof(arr[0]);

    SumAndAverage s1;
    s1.calculateSumAndAverage(arr, size);

    cout << "Sum: " << s1.getSum() << ", Average: " << s1.getAverage() << endl;

    return 0;
}
