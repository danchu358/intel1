#include <iostream>
using namespace std;

const double PI = 3.14159265358979323846;
// 기본 클래스 Shape
class Shape {
public:
    virtual double getArea() = 0;    // 면적을 계산하는 순수 가상 함수
    virtual ~Shape() {}              // 가상 소멸자
};

// Circle 클래스
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double getArea() override {
        return PI * radius * radius; // 원의 면적 계산
    }
};

// Rectangle 클래스
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double getArea() override {
        return width * height;       // 사각형의 면적 계산
    }
};

// Triangle 클래스
class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    double getArea() override {
        return 0.5 * base * height; // 삼각형의 면적 계산
    }
};

// 테스트를 위한 메인 함수
int main() {
    Shape* s1 = new Circle(5);
    Shape* s2 = new Rectangle(4, 5);
    Shape* s3 = new Triangle(3, 4);

    cout << "Circle Area: " << s1->getArea() << endl;
    cout << "Rectangle Area: " << s2->getArea() << endl;
    cout << "Triangle Area: " << s3->getArea() << endl;

    delete s1;                     // 동적으로 할당된 메모리 해제
    delete s2;
    delete s3;

    return 0;
}