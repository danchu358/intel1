#include "template.h"

template <typename T>
double Point<T>::Dist(Point<T> p) // :: �پ������� class �����̴�. �����ϱ� ���� class ������ �Լ��� Ȯ���Ѱ��̴�.
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
void Point<T>::viewP(const char* s)  // ����Ʈ ���� ������Ÿ�Կ��� ���� 
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
Point<T>& Point<T>::operator+(Point<T> p)  // ���� CurP�� p�� + �������� (���ο� Point��) ��ȯ
{
	Point<T>* p1 = new Point<T>(x + p.x, y + p.y); // new�� ������ Ű����, ���ο� ���� Ȯ���ؼ� ���� �������� ��
	return *p1;
}
template <typename T>
Point<T>& Point<T>::operator++()  // ��ü ���� ������ �����ε�
{
	++x; ++y;
	return *this;
}
template <typename T>
Point<T>& Point<T>::operator++(T)  // ��ü ���� ������ �����ε�
{
	Point<T>* p1 = new Point<T>(x++, y++); // new�� ������ Ű����, ���ο� ���� Ȯ���ؼ� ���� �������� ��
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
