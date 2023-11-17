#include <iostream>
#include "haksang1.h"

int main()
{
	haksang1 p1("Lee", 21, "전자공학", 3);
	p1.Show();
	p1.SetSub("국어", 90); p1.Show();
	p1.SetSub("영어", 90); p1.Show();
	p1.SetSub("수학", 90); p1.Show();
	p1.SetSub("미술", 90); p1.Show();
}

//double avg()
//{
//	haksang1.
//}