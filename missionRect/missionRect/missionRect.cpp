#include <iostream>
#include "classes.h"

int main()
{
	Rect r1;
	Rect r2(10, 10, 30, 30);
	Rect r3(Point(20, 20), Point(40, 40));
	r1.show("R1");
	r2.show("R2");
	r3.show("R3");
	double d1 = (r2 + r3).show("R2 + R3").area(); printf("면적은 %.2f입니다.\n", d1);
	double d2 = (r2 - r3).show("R2 - R3").area(); printf("면적은 %.2f입니다.\n", d2);
	double d3 = (r3 - r2).show("R3 - R2").area(); printf("면적은 %.2f입니다.\n", d3);
	double d4 = (r3 * r2); printf("(R3 * R2)의 면적은 %.2f입니다.\n", d4);
}
