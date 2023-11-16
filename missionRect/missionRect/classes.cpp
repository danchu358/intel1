#include "classes.h"

double Point::Dist(Point p) // :: 붙어있으면 class 내부이다. 관리하기 쉽게 class 밖으로 함수를 확장한것이다.
{
	int w = x - p.x;
	int h = y - p.y;
	return sqrt(w * w + h * h);
}
void Point::show(const char* s)  // 디폴트 값은 프로토타입에만 지정 
{
	printf("%s(%d, %d)\n", s, x, y);
}
void Point::showEx(const char* s)  // 디폴트 값은 프로토타입에만 지정 
{
	printf("%s(%d, %d)", s, x, y);
}
Point& Point::operator+(Point p)  // 두점 CurP와 p의 + 연산결과를 (새로운 Point로) 반환
{
	Point* p1 = new Point(x + p.x, y + p.y); // new는 포인터 키워드, 새로운 공간 확보해서 변수 설정해준 것
	return *p1;
}
void Rect::show(const char* s)  // RECT(P1(x1, y1), P2(x2, y2))
{
	printf("%s(", s);
	p1.showEx("P1");
	p2.showEx("P2");
	printf(")\n");
}