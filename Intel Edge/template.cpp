#include "template.h"

template <typename T>
double Point<T>::Dist(Point<T> p) // :: 붙어있으면 class 내부이다. 관리하기 쉽게 class 밖으로 함수를 확장한것이다.
{
	int w = x - p.x;
	int h = y - p.y;
	return sqrt(w * w + h * h);
}
template <typename T>
Point<T>& Point<T>::SetP(Point<T> p)
{
	x = p.x; y = p.y;
	return *this;
}
template <typename T>
Point<T>& Point<T>::SetP(T x, T y)
{
	this->x = x; this->y = y;
	return *this;
}
template <typename T>
void Point<T>::viewP(const char* s)  // 디폴트 값은 프로토타입에만 지정 
{
	printf("%s(%d, %d)\n", s, x, y);
}
template <typename T>
Point<T>& Point<T>::MoveP(T dx, T dy)
{
	this->x += dx; this->y += dy;
	return *this;
}
template <typename T>
Point<T>& Point<T>::operator+(Point<T> p)  // 두점 CurP와 p의 + 연산결과를 (새로운 Point로) 반환
{
	Point<T>* p1 = new Point<T>(x + p.x, y + p.y); // new는 포인터 키워드, 새로운 공간 확보해서 변수 설정해준 것
	return *p1;
}
template <typename T>
Point<T>& Point<T>::operator++()  // 객체 선행 연산자 오버로딩
{
	++x; ++y;
	return *this;
}
template <typename T>
Point<T>& Point<T>::operator++(T)  // 객체 후행 연산자 오버로딩
{
	Point<T>* p1 = new Point<T>(x++, y++); // new는 포인터 키워드, 새로운 공간 확보해서 변수 설정해준 것
	return *p1;
}
template <typename T>
double Point<T>::operator*(Point<T> p)
{
	double w = abs(x - p.x);
	double h = abs(y - p.y);
	double a = w * h;
	return a;
}
//Point3D& Point3D::SetP(Point3D p)
//{
//	X() = p.X(); Y() = p.Y(); z = p.z;
//	return *this;
//}
