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

    //Point(){} // null argument 허용하는 생성자

    Point(int x1 = 0, int y1 = 0)
    {
        x = x1; y = y1;
    }

    int Area(Point p);
    int Area(Point p1, Point p2);
    double Dist(Point p);
    double Dist(Point p1, Point p2);
    double Dist(int x1, int y1);

};

double Point::Dist(Point p1, Point p2)
{
    int w = p1.x - p2.x;
    int h = p1.y - p2.y;
    double d2 = sqrt(w * w + h * h);

    return d2;
}

int Point::Area(Point p1, Point p2)
{
    int w = ABS(p1.x - p2.x);
    int h = ABS(p1.y - p2.y);
    int a2 = w * h;

    return a2;
}

double Point::Dist(Point p)
{
    int w = x - p.x;
    int h = y - p.y;
    double d1 = sqrt(w * w + h * h);

    return d1;
}

int Point::Area(Point p)
{
    int w = ABS(x - p.x);
    int h = ABS(y - p.y);
    int a1 = w * h;

    return a1;
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

    Point p1(10, 10), p2(20, 30), p3;

    double d1 = p1.Dist(p2);
    int a1 = p1.Area(p2);
    double d2 = p1.Dist(p1, p2);
    int a2 = p3.Area(p1, p2);
    
    printf("두 점 p1(%d, %d) p2(%d %d)의 거리는 %.2f, 면적은 %d 입니다.\r\n",
        p1.x, p1.y, p2.x, p2.y, d1, a1);
    printf("두 점 p1(%d, %d) p2(%d %d)의 거리는 %.2f, 면적은 %d 입니다.\r\n", 
        p1.x, p1.y, p2.x, p2.y, d2, a2);
    printf("null argument P3는 p(%d, %d)로 설정되었습니다.", p3.x, p3.y);

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