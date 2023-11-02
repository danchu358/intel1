#pragma once
#include <iostream>
#define MIN(x, y)   (((x) > (y)) ? (y) : (x))
#define MAX(x, y)   (((x) > (y)) ? (x) : (y))

class Point
{
private:  // 접근 지시자(외부 참조 불가)
public:  // 접근 지시자(외부 참조 가능)

    int x, y, z;  // 멤버 변수 선언

    Point(int x = 0, int y = 0) : x(x), y(y) // => initializer
        // 생성자 정의. 함수적 특성(default, overload 등)
    {
        //x = x1; y = y1;
    }

    void SetP(int x1 = 0, int y1 = 0) { x = x1; y = y1; }

    double Dist(Point p)  // 멤버 함수 : 두 점간의 거리 계산. Double 값으로 return
    {
        int w = x - p.x;
        int h = y - p.y;

        return sqrt((w * w) + (h * h)); // sqrt 함수 자료형이 double형이다
    }

    double Dist(Point p1, Point p2)  // 멤버 함수 : 두 점간의 거리 계산. Double 값으로 return
    {
        int w = p1.x - p2.x;
        int h = p1.y - p2.y;

        return sqrt((w * w) + (h * h)); // sqrt 함수 자료형이 double형이다
    }
};

class Rect
{
public:
    Point a, b; // 클래스 멤버변수 선언
    //Point LL, LR, UL, UR; // 외부참조대상

    Rect(Point p1, Point p2)
    {
        a = p1; b = p2;
        /*int xlf = MIN(p1.x, p2.x);
        int xrt = MAX(p1.x, p2.x);
        int ylw = MIN(p1.y, p2.y);
        int yup = MAX(p1.y, p2.y);
        LL = Point(xlf, ylw);
        LR = Point(xrt, ylw);
        UL = Point(xlf, yup);
        UR = Point(xrt, yup);*/
    }

    /*Point GetLL()
    {
        return Point(MIN(a.x, b.x), MIN(a.y, b.y));
    }
    Point GetLR()
    {
        return Point(MAX(a.x, b.x), MIN(a.y, b.y));
    }
    Point GetUL()
    {
        return Point(MIN(a.x, b.x), MAX(a.y, b.y));
    }
    Point GetUR()
    {
        return Point(MAX(a.x, b.x), MAX(a.y, b.y));
    }*/
};