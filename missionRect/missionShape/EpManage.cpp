#include <iostream>
using namespace std;

class Employee {
protected:
    char* Name = NULL;  // char 1byte, «—±€¿∫ 2byte
public:
    int Age;

    Employee(const char* name, int age) : Age(age) {
        rename(Name);
    }
    ~Employee()
    {
        if (Name) delete Name;
    }
    Employee& rename(const char* name)
    {
        if (Name) delete Name;
        Name = new char[strlen(name) + 1];
        strcpy(Name, name);
        return *this;
    }
    void Show()
    {
        printf("%s(%d)\n", Name, Age);
    }
};

class Manager : public Employee {
    char* Position = NULL;
public:
    Manager(const char* Name, int age, const char* position)
        : Employee(Name, age)
    {
        rePosition(position);
    }
    ~Manager()
    {
        if (Position) delete Position;
    }
    Manager& rePosition(const char* position)
    {
        if (Position) delete Position;
        Position = new char[strlen(position) + 1];
        strcpy(Position, position);
        return *this;
    }
};

class Developer : public Employee {
    char* Language = NULL;
public:
    Developer(const char* Name, int age, const char* language)
        : Employee(Name, age)
    {
        rename(language);
    }
    ~Developer()
    {
        if (Language) delete Language;
    }
    Developer& addLanguage(const char* language)
    {
        if (Language) delete Language;
        Language = new char[strlen(Language) + strlen(language) + 1];
        strcpy(Language, language);
        return *this;
    }
};