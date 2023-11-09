#include "Point.h"

double Point::Dist(Point p) // :: 붙어있으면 class 내부이다. 관리하기 쉽게 class 밖으로 함수를 확장한것이다.
{	
	int w = x - p.x;
	int h = y - p.y;
	return sqrt(w * w + h * h);
}
Point& Point::SetP(Point p)
{
	x = p.x; y = p.y; 
	return *this;
}
Point& Point::SetP(int x, int y)
{
	this->x = x; this->y = y; 
	return *this;
}
void Point::viewP(const char *s)  // 디폴트 값은 프로토타입에만 지정 
{
	printf("%s(%d, %d)\n", s, x, y);
}
Point& Point::MoveP(int dx, int dy)
{
	this->x += dx; this->y += dy;
	return *this;
}
Point& Point::operator+(Point p)  // 두점 CurP와 p의 + 연산결과를 (새로운 Point로) 반환
{
	Point *p1 = new Point(x + p.x, y + p.y); // new는 포인터 키워드, 새로운 공간 확보해서 변수 설정해준 것
	return *p1;
}
Point& Point::operator++()  // 객체 선행 연산자 오버로딩
{
	++x; ++y;
	return *this;
}
Point& Point::operator++(int)  // 객체 후행 연산자 오버로딩
{
	Point* p1 = new Point(x++, y++); // new는 포인터 키워드, 새로운 공간 확보해서 변수 설정해준 것
	return *p1;
}
double Point::operator*(Point p)
{
	double w = abs(x - p.x);
	double h = abs(y - p.y);
	double a = w * h;
	return a;
}
Point3D& Point3D::SetP(Point3D p)
{
	X() = p.X(); Y() = p.Y(); z = p.z;
	return *this;
}
