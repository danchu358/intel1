#include <iostream>

#define SQUARE(x) ((x) * (x))
#define ABS(x) (((x) < 0) ? -(x) : (x))

//typedef struct Point
//{
//    int x;
//    int y;
//} Point2D;
//double Dist(Point2D p1, Point2D p2);

//class Point
//{
//public:
//    int x;
//    int y;
//
//    Point(int x1, int y1)
//    {
//        x = x1; y = y1;
//    }
//
//    double Dist(Point p);
//
//};

class Point
{
public:
    int x;
    int y;

    Point(int x1, int y1)
    {
        x = x1; y = y1;
    }

    int Area(Point p);
    double Dist(Point p);

};

double Point::Dist(Point p)
{
    int w = x - p.x;
    int h = y - p.y;
    double d = sqrt(w * w + h * h);

    return d;
}

int Point::Area(Point p)
{
    int w = ABS(x - p.x);
    int h = ABS(y - p.y);
    int a = w * h;

    return a;
}

int main()
{
    /*printf("안녕하세요. 환영합니다. C++\n\n");
    printf("2의 제곱 : %d\n", SQUARE(2));
    printf("5의 제곱 : %d\n", SQUARE(5));
    printf("1.2의 제곱 : %f\n", SQUARE(1.2));

    int x = -7;
    printf("%d의 제곱 : %d\n", x ,SQUARE(x));
    printf("%d의 절댓값 : %d\n", x, ABS(x));*/

    Point p1(10, 10), p2(20, 30);
    /*p1.x = 10; p1.y = 10;
    p2.x = 20; p2.y = 30;*/

    double d = p1.Dist(p2);
    printf("두 점 p1(%d, %d) p2(%d %d)의 거리는 %.2f 입니다.\n\n", 
        p1.x, p1.y, p2.x, p2.y, d);

    int a = p1.Area(p2);
    printf("두 점 p1(%d, %d) p2(%d %d)의 넓이는 %d 입니다.\n\n",
        p1.x, p1.y, p2.x, p2.y, a);
}

//double Dist(Point2D p1, Point2D p2) //두 점간의 거리
//{
//    int w = ABS(p1.x - p2.x);
//    int h = ABS(p1.y - p2.y);
//    int w1 = w * w;
//    int h1 = h * h;
//    double d = sqrt(w1 + h1);
//
//    return d;
//
//}