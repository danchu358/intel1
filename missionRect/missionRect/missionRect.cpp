#include <iostream>
#include "classes.h"

int main()
{
	Rect r1;
	Rect r2(10, 20, 30, 40);
	Rect r3(Point(100, 200), Point(300, 400));
	r1.show("R1");
	r2.show("R2");
	r3.show("R3");
}
