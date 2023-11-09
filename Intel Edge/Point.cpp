#include "Point.h"

double Point::Dist(Point p) // :: �پ������� class �����̴�. �����ϱ� ���� class ������ �Լ��� Ȯ���Ѱ��̴�.
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
void Point::viewP(const char *s)  // ����Ʈ ���� ������Ÿ�Կ��� ���� 
{
	printf("%s(%d, %d)\n", s, x, y);
}
Point& Point::MoveP(int dx, int dy)
{
	this->x += dx; this->y += dy;
	return *this;
}
Point& Point::operator+(Point p)  // ���� CurP�� p�� + �������� (���ο� Point��) ��ȯ
{
	Point *p1 = new Point(x + p.x, y + p.y); // new�� ������ ������ Ű����, ���ο� ���� Ȯ���ؼ� ���� �������� ��
	return *p1;
}
Point3D& Point3D::SetP(Point3D p)
{
	X() = p.X(); Y() = p.Y(); z = p.z;
	return *this;
}