#include <iostream>
#include <string>

using namespace std;

class Employee {
protected:
    string name;
    int employeeId;

public:
    Employee(string name, int employeeId) : name(name), employeeId(employeeId) {}

    virtual void displayInfo() {
        cout << "직원 이름: " << name << endl;
        cout << "직원 ID: " << employeeId << endl;
    }
};

class Manager : public Employee {
private:
    int numberOfSubordinates;

public:
    Manager(string name, int employeeId, int numberOfSubordinates)
        : Employee(name, employeeId), numberOfSubordinates(numberOfSubordinates) {}

    void displayInfo() override {
        Employee::displayInfo();
        cout << "직원 수: " << numberOfSubordinates << endl;
    }
};

class Developer : public Employee {
private:
    string programmingLanguage;

public:
    Developer(string name, int employeeId, string programmingLanguage)
        : Employee(name, employeeId), programmingLanguage(programmingLanguage) {}

    void displayInfo() override {
        Employee::displayInfo();
        cout << "프로그래밍 언어: " << programmingLanguage << endl;
    }
};

int main() {
    Employee emp("홍길동", 1001);
    Manager manager("김매니저", 2001, 5);
    Developer developer("이개발자", 3001, "C++");

    cout << "Employee 정보:" << endl;
    emp.displayInfo();
    cout << endl;

    cout << "Manager 정보:" << endl;
    manager.displayInfo();
    cout << endl;

    cout << "Developer 정보:" << endl;
    developer.displayInfo();
    cout << endl;

    return 0;
}
