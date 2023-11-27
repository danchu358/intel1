#include <iostream>

class ArrTest
{
private:
    int* arr;
    int Len;
public:
    ArrTest(int size) : Len(size)
    {
        arr = new int[size];
    }
    ~ArrTest()
    {
        delete arr;
    }
    int length()
    {
        return Len;
    }
    int& operator[](int idx)  // calling sequence : arr[n]
    {
        if (idx < 0 || idx >= Len - 1)
        {
            std::cout << "Out of bound\n"; exit(1);
        }
        return arr[idx];
    }
    void show();
    ArrTest& append(int size);
    ArrTest& append(ArrTest& brr);
};
void ArrTest::show()
{
    printf("{ ");
    for (int i = 0; i < Len - 1; i++) { printf("%d, ", arr[i]); }
    printf("%d", arr[Len - 1]);
    printf(" }\n");
}
ArrTest& ArrTest::append(int size)
{
    int* arr1 = new int[Len + size];  // 확장된 메모리
    memcpy(arr1, arr, Len * sizeof(int));
    delete arr;
    arr = arr1;
    Len += size;
    return *this;
}
ArrTest& ArrTest::append(ArrTest& brr)
{
    int* arr1 = new int[this->Len + brr.length()];
    memcpy(arr1, arr, Len * sizeof(int));
    memcpy(arr1 + Len, brr.arr, brr.length() * sizeof(int));
    delete arr;
    arr = arr1;
    Len += brr.length();
    return *this;
}

class Func
{
public:
    int operator()(int a, int b)
    {
        return a * b;
    }
    double operator()(double a, double b)
    {
        return a * b;
    }
    ArrTest& operator()(ArrTest& b1, ArrTest& b2)
    {
        return b1.append(b2);
    }
};

int main()
{
    int a1[] = { 15, 12, 13, 11, 14 };
    ArrTest arr(5);
    for (int i = 0; i < 5; i++)             arr[i] = a1[i];
    //for (int i = 0; i < arr.length(); i++)  printf("ArrTest[%d] = %d\n", i, arr[i]);
    //
    int a2[] = { 21, 22, 23, 24, 25 };
    ArrTest brr(5);
    for (int i = 0; i < 5; i++)             brr[i] = a2[i];
    //for (int i = 0; i < brr.length(); i++)  printf("ArrTest[%d] = %d\n", i, brr[i]);
    //
    //int n = arr.length();
    //printf("배열 확장 %d --> %d\n", n, arr.append(brr).length());
    //
    ////printf("배열 확장 %d --> %d\n", arr.length(), arr.append(10).length());  // c언어 특성상 주소크기가 뒤에서 이미 변경되어 앞에도 같은 크기 출력됨
    //for (int i = 0; i < arr.length(); i++)  printf("ArrTest[%d] = %d\n", i, arr[i]);
    Func mul;
    std::cout << mul(2, 3) << "\n";
    std::cout << mul(2.5, 3.7) << "\n";
    mul(arr, brr).show();
}

