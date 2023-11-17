#pragma once
#include <iostream>
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

class person
{
protected:
	char* name = NULL;  // char 1byte, 한글은 2byte
public:
	int Age;

	//person(int age = 0) : Age(age) {}  // NULL 생성자
	person(const char* Name, int age) : Age(age)
	{
		rename(Name);
	}
	~person()
	{
		if (name) delete name;
	}
	person& rename(const char* Name)
	{
		if(name) delete name;
		name = new char[strlen(Name) + 1];
		strcpy(name, Name);
		return *this;
	}
	void Show()
	{
		printf("%s(%d)\n", name, Age);
	}
};

class subject
{
	char* Name = NULL;
public:
	int Score;

	subject() {};
	subject(const char* name, int score = 0) : Score(score)
	{
		reSub(name);
	}
	subject& reSub(const char* name)
	{
		if (Name) delete Name;
		Name = new char[strlen(name) + 1];
		strcpy(Name, name);
		return *this;
	}
	char* name() { return (char*)Name; }
};

class haksang1 : public person
	{
		char* Major = NULL;
	public:
		int Grade;
		int SubNum = 0;  // 수강과목 수
		subject sub[10];  // kor, eng;

		haksang1(const char* Name, int age, const char* major, int grade)
			: person(Name, age), Grade(grade)
		{
			reMajor(major);
		}
		~haksang1()
		{
			if(Major) delete Major;
		}
		void SetSub(const char* name, int score)
		{
			if (SubNum > 10) return;
			sub[SubNum++].reSub(name).Score = score;
		}
		haksang1& reMajor(const char* major)
		{
			if (Major) delete Major;
			Major = new char[strlen(major) + 1];
			strcpy(Major, major);
			return *this;
		}
		void Show()
		{
			((person*)this)->Show();
			printf("%s %d\n", Major, Grade);
			for (int i = 0; i < SubNum; i++) {
				printf("%s : %d\n", sub[i].name(), sub[i].Score);
			}
		}
	};