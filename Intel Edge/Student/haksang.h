#pragma once
class person
{
	char *name;
	int Age;
public:
	person()
	{
		name = new char[100];
	}
	~person()
	{
		delete name;
	}
};

class haksang
{

};