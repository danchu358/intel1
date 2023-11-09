#pragma once
//#include <corecrt_math.h>
//extern double sqrt(double);
#include <iostream>

class Point
{
private:
	int x;
	int y;

public:
	Point(int x1 = 0, int y1 = 0) : x(x1), y(y1){}

	Point& SetP(Point P);   // Self-Reference
	Point& SetP(int x, int y);
	Point& MoveP(int off_x, int off_y); // Move Point position
	double Dist(Point p);  // Distance
	void viewP(const char * s = NULL); // View Current Point
	int& X() { return x; }; // 프라이빗 접근자 맴버 변수 에서 퍼블릭 접근자로 바꾸는 함수
	int& Y() { return y; }; //프라이빗 접근자 맴버 변수 에서 퍼블릭 접근자로 바꾸는 함수
	Point& operator+(Point p);
};

class Point3D : public Point    // 클래스 상속 정의
{
private:	
	int z;

public:
	Point3D(int x = 0 , int y = 0, int z = 0) : Point(x , y), z(z)
	{}
	Point3D& SetP(Point3D p);
	double Dist3D(Point3D p)    // Distance 3D
	{
		int w = X() - p.X();
		int h = Y() - p.Y(); // 상위클래스 protected 접근 가능
		int d = z - p.z; //하위클래스 내부이기에 프라이빗 int z 접근가능
		return sqrt((w * w) + (h * h) + (d * d));
	}
};