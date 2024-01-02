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
        cout << "���� �̸�: " << name << endl;
        cout << "���� ID: " << employeeId << endl;
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
        cout << "���� ��: " << numberOfSubordinates << endl;
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
        cout << "���α׷��� ���: " << programmingLanguage << endl;
    }
};

int main() {
    Employee emp("ȫ�浿", 1001);
    Manager manager("��Ŵ���", 2001, 5);
    Developer developer("�̰�����", 3001, "C++");

    cout << "Employee ����:" << endl;
    emp.displayInfo();
    cout << endl;

    cout << "Manager ����:" << endl;
    manager.displayInfo();
    cout << endl;

    cout << "Developer ����:" << endl;
    developer.displayInfo();
    cout << endl;

    return 0;
}
