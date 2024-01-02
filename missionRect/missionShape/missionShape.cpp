#include <iostream>
using namespace std;

const double PI = 3.14159265358979323846;

class Shape {
public:
    virtual double getArea() = 0;    
    virtual ~Shape() {}              
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double getArea() override {
        return PI * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double getArea() override {
        return width * height;
    }
};

class Triangle : public Shape {
private:
    double base, height;
public:
    Triangle(double b, double h) : base(b), height(h) {}
    double getArea() override {
        return 0.5 * base * height;
    }
};

int main() {
    Shape* s1 = new Circle(5);
    Shape* s2 = new Rectangle(4, 5);
    Shape* s3 = new Triangle(3, 4);

    cout << "Circle Area: " << s1->getArea() << endl;
    cout << "Rectangle Area: " << s2->getArea() << endl;
    cout << "Triangle Area: " << s3->getArea() << endl;

    delete s1;                     
    delete s2;
    delete s3;

    return 0;
}