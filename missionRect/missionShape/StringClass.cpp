#include <iostream>
#include <cstring>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

class String {
private:
    char* str;
    int length;

public:
    String() : str(nullptr), length(0) {}
    String(const char* s) : length(strlen(s)) {
        str = new char[length + 1];
        strcpy(str, s);
    }

    ~String() {
        delete[] str;
    }

    String(const String& other) : length(other.length) {
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    String operator+(const String& other) const {
        String result;
        result.length = length + other.length;
        result.str = new char[result.length + 1];
        strcpy(result.str, str);
        strcat(result.str, other.str);
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.str;
        return os;
    }

    bool operator!=(const String& other) const {
        return strcmp(str, other.str) != 0;
    }

    bool operator==(const String& other) const {
        return strcmp(str, other.str) == 0;
    }

    String& operator+=(const String& other) {
        char* newStr = new char[length + other.length + 1];
        strcpy(newStr, str);
        strcat(newStr, other.str);
        delete[] str;
        str = newStr;
        length += other.length;
        return *this;
    }

    int find(const String& target) const {
        char* ptr = strstr(str, target.str);
        if (ptr == nullptr) {
            return -1;
        }
        return ptr - str;
    }

    String substr(int start, int count) const {
        if (start < 0 || start >= length || count <= 0) {
            return String();
        }
        if (start + count > length) {
            count = length - start;
        }
        char* subStr = new char[count + 1];
        strncpy(subStr, str + start, count);
        subStr[count] = '\0';
        return String(subStr);
    }

    String replace(const String& target, const String& replacement) const {
        String result(*this);
        int pos = result.find(target);
        while (pos != -1) {
            result = result.substr(0, pos) + replacement + result.substr(pos + target.length, result.length - pos - target.length);
            pos = result.find(target);
        }
        return result;
    }
};

int main() {
    String s1("Hello");
    String s2("World");

    String s3 = s1 + " " + s2;
    std::cout << "s3: " << s3 << std::endl;

    String s4 = "Hello";
    std::cout << "s4: " << s4 << std::endl;

    std::cout << "s4 != s3: " << (s4 != s3) << std::endl;
    std::cout << "s4 == s3: " << (s4 == s3) << std::endl;

    s4 += " C++";
    std::cout << "s4 += \" C++\": " << s4 << std::endl;

    int pos = s3.find("World");
    if (pos != -1) {
        std::cout << "Found 'World' at position " << pos << std::endl;
    }
    else {
        std::cout << "Not found 'World'" << std::endl;
    }

    String s5 = s3.substr(6, 5);
    std::cout << "s5: " << s5 << std::endl;

    String s6 = s3.replace("World", "C++");
    std::cout << "s6: " << s6 << std::endl;

    return 0;
}
