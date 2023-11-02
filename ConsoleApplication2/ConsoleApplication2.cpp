#include <iostream>
#include "./header/Point.h"
#define MIN(x, y)   (((x) > (y)) ? (y) : (x))
#define MAX(x, y)   (((x) > (y)) ? (x) : (y))

void printP(Point p)
{
    printf("Point(%d, %d)\n", p.x, p.y);
}
void swap_v(int a, int b) // call-by-value
{
    int t(a);
    printf("swap 초기값 a = %d  b = %d\n", a, b);
    a = b; b = t;
    printf("swap 결과값 a = %d  b = %d\n",a, b);
}
void swap_p(int *a, int *b) // call-by-reference
{
    int t(*a);
    printf("swap 초기값 a = %d  b = %d\n", *a, *b);
    *a = *b; *b = t;
    printf("swap 결과값 a = %d  b = %d\n", *a, *b);
}
void swap_r(int& a, int& b) //call-by-reference(using ref. variables)
{
    int t(a);
    printf("[swar_r] a = %d  b = %d\n", a, b);
    a = b; b = t;
    printf("[swar_r] a = %d  b = %d\n", a, b);
}
    
int main()
{
    Point arr[3];  // 객체 배열 3개의 Point 클래스 객체가 defalut 초기화됨
    arr[0].SetP(10, 10); printP(arr[0]);
    arr[1].SetP(20, 30); printP(arr[1]);
    arr[2].SetP(40, 60); printP(arr[2]);
    printf("Class Point 객체 크기 : %d\n", sizeof(arr));

    Point* Parr[3];  // Point 객체 포인터(*) 배열 : 객체화 되어 있지 않음
    printf("Point 객체 포인터 배열 크기 : %d\n", sizeof(Parr));
    Parr[0] =  new Point(10, 10);  printP(*Parr[0]);
    Parr[1] = new Point(20, 30);  printP(*Parr[1]);
    Parr[2] = new Point(40, 60);  printP(*Parr[2]);

    /*Point p1, p2(10, 10), p3(20, 30), p4;
    p4 = p3;
    double d1 = p1.Dist(p2);
    double d2 = p2.Dist(p3);
    double d3 = p1.Dist(p3);

    printP(p4);
    printP(p1);
    printP(p2);
    printP(p3);
    printf("점간의 거리 계산 : (p1, p2) = %.2f (p2, p3) = %.2f (p1, p3) = %.2f\n", d1, d2, d3);

    Rect r(p2, p3);
    printf("두 점\n");
    printP(p2);
    printP(p3);
    printf("에 의해 정의된 사각형의 4점의 좌표는\n");
    printP(r.GetLL());
    printP(r.GetLR());
    printP(r.GetUL());
    printP(r.GetUR());*/

    ////reference 변수 테스트
    //int a(10), b(20);
    //printf("초기값 a = %d  b = %d\n", a, b);
    //swap_r(a, b);
    //printf("결과값 후 a = %d  b = %d\n",a, b);

    //int n = 1234, n1 = 1000;
    //int& m = n;
    //printf("레퍼런스 변수 테스트 n = %d, m = %d\n", n, m);
    //m = 5678;
    //printf("레퍼런스 변수 테스트 n = %d, m = %d\n", n, m);
}
