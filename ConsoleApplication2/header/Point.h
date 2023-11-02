#pragma once
#include <iostream>
#define MIN(x, y)   (((x) > (y)) ? (y) : (x))
#define MAX(x, y)   (((x) > (y)) ? (x) : (y))

class Point
{
private:  // ���� ������(�ܺ� ���� �Ұ�)
public:  // ���� ������(�ܺ� ���� ����)

    int x, y, z;  // ��� ���� ����

    Point(int x = 0, int y = 0) : x(x), y(y) // => initializer
        // ������ ����. �Լ��� Ư��(default, overload ��)
    {
        //x = x1; y = y1;
    }

    void SetP(int x1 = 0, int y1 = 0) { x = x1; y = y1; }

    double Dist(Point p)  // ��� �Լ� : �� ������ �Ÿ� ���. Double ������ return
    {
        int w = x - p.x;
        int h = y - p.y;

        return sqrt((w * w) + (h * h)); // sqrt �Լ� �ڷ����� double���̴�
    }

    double Dist(Point p1, Point p2)  // ��� �Լ� : �� ������ �Ÿ� ���. Double ������ return
    {
        int w = p1.x - p2.x;
        int h = p1.y - p2.y;

        return sqrt((w * w) + (h * h)); // sqrt �Լ� �ڷ����� double���̴�
    }
};

class Rect
{
public:
    Point a, b; // Ŭ���� ������� ����
    //Point LL, LR, UL, UR; // �ܺ��������

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