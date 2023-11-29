#include <iostream>
#include "template.h"

int main()
{
	Point<int> p1(10, 10), p2, p3;
	p1.viewP("p1"); p2.viewP(); p3.viewP();
	Point<int> p4 = p3, p5(p2);
	
	p2.SetP(Point<int>(20, 30)).viewP("p2");
	p3.SetP(40, 70).viewP("p3");
	printf("p2와 p3의 좌표로 계산되는 면적 : %.2f\n", p2 * p3);
	/*printf("Point Move Test.....\n");
	p1.MoveP(1, 1).viewP("P1_1_1");
	p1.MoveP(1, 1).viewP("P1_1_1"); 
	p1.MoveP(1, 1).viewP("P1_1_1"); 
	p1.MoveP(1, 1).viewP("P1_1_1"); 
	printf("Point print Test..p1(%d, %d).\n\n", p1.X(), p1.Y());   
	p1.X() = 10; p1.Y() = 10;
	printf("Point Ref.Access print Test..."); p1.viewP("p1");*/

	Point<T> p6 = p2 + p1;
	printf("Point [Operator+] Test..."); p6.viewP("_p6");
	printf("Point [Operator++] 후행연산Test..."); p6++.viewP("_p6");
	printf("Point [Operator++] 선행연산 Test..."); (++p6).viewP("_p6");

	//Point3D pp0, pp1(10, 20, 30);
	//double d3 = pp0.Dist3D(pp1);
	//double d2 = pp0.Dist(Point(10, 20));  // 하위 클래스인데 상위 클래스 상속을 통해서 거리계산이 가능하다 
	//printf("pp0(0, 0, 0) 과 pp1 (10, 20, 30)의 거리는 %f\n", d3);
	//printf("pp0(0, 0, 0) 과 p1 (10, 20) 의 거리는 %f\n", d2);
	//p1.viewP("p1"); p2.viewP("p2"); p3.viewP("p3");
}

