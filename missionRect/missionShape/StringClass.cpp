#include <iostream>
using namespace std;

class String {
private:
    int* arr;
    int Len;
public:
    String(int size) : Len(size)
    {
        arr = new int[size];
    }
    ~String()
    {
        delete arr;
    }
    int length()
    {
        return Len;
    }
    int& operator[](int idx)
    {
        if (idx < 0 || idx > Len - 1)
        {
            cout << "Out of bound\n"; exit(1);
        }
        return arr[idx];
    }
    String& operator+(String& br)
    {
        int l = Len + br.length();
        String* cr = new String(l);
        memcpy(cr->arr, arr, Len * sizeof(int));
        memcpy(cr->arr + Len, br.arr, br.length() * sizeof(int));
        return *cr;
    }
    String& append(String& br)
    {
        int l = Len + br.length();
        String* cr = new String(l);
        memcpy(cr->arr + Len, br.arr, br.length() * sizeof(int));
        delete arr;
        Len += br.length() * sizeof(int);
        return *this;
    }
    String& operator+=(String& br)
    {
        return this->append(br);
    }
    String& operator-=(int idx)
    {
        if (idx < 0 || idx > Len - 1)
        {
            cout << "Out of bound\n";
            exit(1);
        }

        char* subStr = new char[idx + 1]; // 부분 문자열을 저장할 새로운 배열
        for (int i = 0; i < idx; i++) {
            subStr[i] = arr[i]; // 원본 문자열에서 부분 복사
        }
        subStr[idx] = '\0'; // 문자열의 끝을 나타내는 null 문자 추가

        String result = *subStr;
        delete[] subStr;       // 임시 배열 메모리 해제

        return result;
    }
    bool operator==(String& br)
    {
        if (Len != br.Len) {
            cout << "Error" << endl;
            return false;
        }
        for (int i = 0; i < Len; i++) {
            if (arr[i] != br[i])
                return false;
        }
        return true;
    }
    friend ostream& operator<<(ostream& os, String& ar)
    {
        int i;
        printf("{ ");
        for (i = 0; i < ar.Len - 1; i++)
            cout << ar.arr[i] << ", ";
        cout << ar.arr[i];
        printf(" }");
        return os;
    }
};

int main()
{
    string s1 = "안녕하세요";
    string s2 = "잘지내시나요";
    cout << s1 << "\n";
    cout << s2 << "\n";
    cout << s1 + s2 << "\n";
    
    string s3 = s1 + s2;
    cout << (s1 += s2) << "\n";
    cout << s3 << "\n";

    const char* a = "anasdfedfhge\n";
    string b = a -= 3;
    cout << b << "\n";
}