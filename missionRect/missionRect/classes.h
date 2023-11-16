#pragma once
#include <iostream>
#define		abs(x)		((x)<0)?-(x):(x)
#define		min(x, y)	((x)<(y))?(x):(y)
#define		max(x, y)	((x)>(y))?(x):(y)

class Point
{
private:
public:
	int x;
	int y;

	Point(int x1 = 0, int y1 = 0) : x(x1), y(y1) {}

	double Dist(Point p);  // Distance
	void show(const char* s = NULL); // View Current Point, s : Point name
	void showEx(const char* s = NULL); // View Current Point, no Linefeed

	Point& operator+(Point p);
};

class Rect
{
private:
	void Init()
	{
		LL = Point(min(p1.x, p2.x), min(p1.y, p2.y));
		LR = Point(max(p1.x, p2.x), min(p1.y, p2.y));
		UL = Point(min(p1.x, p2.x), max(p1.y, p2.y));
		UR = Point(max(p1.x, p2.x), max(p1.y, p2.y));
	}
public:
	Point p1, p2;
	Point LL, LR, UL, UR;
	int x1, x2, y1, y2;

	Rect(Point pp1, Point pp2) : p1(pp1), p2(pp2), 
		x1(pp1.x), y1(pp1.y), x2(pp2.x), y2(pp2.y)
	{
		Init();
	}
	Rect(int xx1 = 0, int yy1 = 0, int xx2 = 0, int yy2 = 0)  // 생성자 오버로드
	{
		x1 = xx1; y1 = yy1;
		x2 = xx2; y2 = yy2;
		p1 = Point(x1, y1);
		p2 = Point(x2, y2);
		Init();
	}
	double area();
	Rect& show(const char* s);  // Rect(P1(x1, y1), P2(x2, y2))
	Rect& operator+(Rect r);
	Rect& operator-(Rect r);
	double operator*(Rect r);
};