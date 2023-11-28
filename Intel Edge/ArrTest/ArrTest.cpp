#include <iostream>
using namespace std;

template <typename T>
class ArrTest
{
private:
    T* arr;
    int Len;
public:
    ArrTest(int size) : Len(size)
    {
        arr = new T[size];
    }
    ~ArrTest()
    {
        delete arr;
    }
    int length()
    {
        return Len;
    }
    T& operator[](int idx)  // calling sequence : arr[n]
    {
        if (idx < 0 || idx > Len - 1)
        {
            std::cout << "Out of bound\n"; exit(1);
        }
        return arr[idx];
    }
    ArrTest<T>& operator+(ArrTest<T>& br)  // calling sequence : crr = arr + brr
    {
        int l = Len + br.length();
        ArrTest<T> *cr = new ArrTest<T>(l);
        memcpy(cr->arr, arr, Len * sizeof(T));
        memcpy(cr->arr + Len, br.arr, br.length() * sizeof(T));
        return *cr;
    }
    ArrTest<T>& operator+=(ArrTest<T>& br)  // calling sequence : arr += brr
    {
        return this->append(br);
    }
    bool operator==(ArrTest<T>& br)  // calling sequence : if(arr == brr)
    {
        if (Len != br.Len)  return false;
        for (int i = 0; i < Len; i++) {
            if (arr[i] != br[i])  return false;
        }
        return true;
    }
    void show()
    {
        printf("{ ");
        for (int i = 0; i < Len - 1; i++) {
            cout << arr[i] << ", "; cout << arr[i];
        }
        printf(" }\n");
    }
    ArrTest& append(int size)
    {
        T* arr1 = new T[Len + size];  // 확장된 메모리
        memcpy(arr1, arr, Len * sizeof(T));
        delete arr;
        arr = arr1;
        Len += size;
        return *this;
    }
    ArrTest& append(ArrTest& brr)
    {
        T* arr1 = new T[this->Len + brr.length()];
        memcpy(arr1, arr, Len * sizeof(T));
        memcpy(arr1 + Len, brr.arr, brr.length() * sizeof(T));
        delete arr;
        arr = arr1;
        Len += brr.length();
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, ArrTest& ar)
    {
        int i;
        printf("{ ");
        for (i = 0; i < ar.Len - 1; i++)
            cout << ar.arr[i] << ", "; cout << ar.arr[i];
        printf(" }");
        return os;
    }
    
};

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
    ArrTest<int>& operator()(ArrTest<int>& b1, ArrTest<int>& b2)
    {
        return b1.append(b2);
    }
    ArrTest<double>& operator()(ArrTest<double>& b1, ArrTest<double>& b2)
    {
        return b1.append(b2);
    }
};

int main()
{
    double a1[] = { 11.1, 22.1, 33.1, 44.1, 55.1 };
    ArrTest<double> arr(5);
    for (int i = 0; i < 5; i++)             arr[i] = a1[i];
    //for (int i = 0; i < arr.length(); i++)  printf("ArrTest[%d] = %d\n", i, arr[i]);
    //
    double a2[] = { 21.1, 22.1, 23.1, 24.1, 25.1 };
    ArrTest<double> brr(5);
    for (int i = 0; i < 5; i++)             brr[i] = a2[i];
    //for (int i = 0; i < brr.length(); i++)  printf("ArrTest[%d] = %d\n", i, brr[i]);
    //
    //int n = arr.length();
    //printf("배열 확장 %d --> %d\n", n, arr.append(brr).length());
    //
    ////printf("배열 확장 %d --> %d\n", arr.length(), arr.append(10).length());  // c언어 특성상 주소크기가 뒤에서 이미 변경되어 앞에도 같은 크기 출력됨
    //for (int i = 0; i < arr.length(); i++)  printf("ArrTest[%d] = %d\n", i, arr[i]);
    
    if (arr == brr) printf("Same sequence....\n");
    ArrTest<double> crr = arr + brr;
    Func mul;
    cout << mul(2, 3) << "\n";
    cout << mul(2.3, 3.6) << "\n";
    cout << mul(arr, brr) << "\n";
    cout << (arr += brr) << "\n";
    cout << crr << "\n";

    string s = "안녕하세요";
    cout << s << "\n";
    cout << s.substr(2, 4) << "\n";  // substr은 byte단위로 표현됨. 한글은 2byte 문자라서 고려해야됨
    //s.substr(2, 2);
}

