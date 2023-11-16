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
	p1 = (new Point(x + p.x, y + p.y));
	return *p1;
}
Rect& Rect::show(const char* s)  // RECT(P1(x1, y1), P2(x2, y2))
{
	printf("%s(", s);
	LL.showEx("P1");
	UR.showEx("P2");
	printf(")\n");
	return *this;
}
double Rect::area()
{
	return (double)(abs((p1.x - p2.x) * (p1.y - p2.y)));
}
Rect& Rect::operator+(Rect r)
{
	int x1 = min(min(this->x1, this->x2), min(r.x1, r.x2)); // this를 사용해서 같은 변수 이름을 사용할 수 있다.
	int x2 = max(min(this->x1, this->x2), max(r.x1, r.x2));
	int y1 = min(min(this->y1, this->y2), min(r.y1, r.y2));
	int y2 = max(min(this->y1, this->y2), max(r.y1, r.y2));
	/*
	int xx1 = min(min(x1, x2), min(r.x1, r.x2));
	int xx2 = max(min(x1, x2), max(r.x1, r.x2));
	int yy1 = min(min(y1, y2), min(r.y1, r.y2));
	int yy2 = max(min(y1, y2), max(r.y1, r.y2));
	*/
	return *(new Rect(x1, y1, x2, y2));
}
Rect& Rect::operator-(Rect r)
{
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;
	Rect& rr = *this;

	// 두 사각형이 겹치지 않는 경우 0 Rect 반환
	if (rr.LR.x < r.LL.x || r.LR.x < rr.LL.x) return *(new Rect(0, 0, 0, 0));
	if (rr.UL.y < r.LL.y || r.UL.y < rr.LL.y) return *(new Rect(0, 0, 0, 0));

	x1 = min(min(rr.x1, rr.x2), min(r.x1, r.x2));
	x2 = max(rr.LL.x, r.LL.x);
	x3 = min(rr.LR.x, r.LR.x);
	x4 = max(max(rr.x1, rr.x2), max(r.x1, r.x2));

	y1 = min(min(rr.y1, rr.y2), min(r.y1, r.y2));
	y2 = min(rr.UL.y, r.UL.y);
	y3 = max(rr.LL.y, r.LL.y);
	y4 = max(max(rr.y1, rr.y2), max(r.y1, r.y2));

	return *(new Rect(x2, y2, x3, y3));
}
double Rect::operator*(Rect r)
{
	double d1 = area();
	double d2 = r.area();
	double d3 = (*(this) - r).area();
	return d1 + d2 - d3;
}