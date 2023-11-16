#include "classes.h"

double Point::Dist(Point p) // :: �پ������� class �����̴�. �����ϱ� ���� class ������ �Լ��� Ȯ���Ѱ��̴�.
{
	int w = x - p.x;
	int h = y - p.y;
	return sqrt(w * w + h * h);
}
void Point::show(const char* s)  // ����Ʈ ���� ������Ÿ�Կ��� ���� 
{
	printf("%s(%d, %d)\n", s, x, y);
}
void Point::showEx(const char* s)  // ����Ʈ ���� ������Ÿ�Կ��� ���� 
{
	printf("%s(%d, %d)", s, x, y);
}
Point& Point::operator+(Point p)  // ���� CurP�� p�� + �������� (���ο� Point��) ��ȯ
{
	Point* p1 = new Point(x + p.x, y + p.y); // new�� ������ Ű����, ���ο� ���� Ȯ���ؼ� ���� �������� ��
	return *p1;
}
void Rect::show(const char* s)  // RECT(P1(x1, y1), P2(x2, y2))
{
	printf("%s(", s);
	p1.showEx("P1");
	p2.showEx("P2");
	printf(")\n");
}