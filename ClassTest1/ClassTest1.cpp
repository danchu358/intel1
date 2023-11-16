#include <iostream>

class First
{
public:
    First()
    {
        printf("First\n");
    }
    virtual ~First()
    {
        printf("~First\n");
    }
};
class Second : public First
{
public:
    Second()
    {
        printf("Second\n");
    }
    ~Second()
    {
        printf("~Second\n");
    }
};
class Third : public Second
{
public:
    Third()
    {
        printf("Third\n");
    }
    ~Third()
    {
        printf("~Third\n");
    }
};

int main()
{
    First* ptr = new Third(); // 생성자는 상속을 받아서 First, Second, Third 순서대로 출력이 되지만, 소멸자는 포인터로 소멸자를 지정할 시 First 소멸자만 실행되고 이후 Second와 Third의 소멸자가 실행
    //되지 않아 Second와 Third의 함수가 소멸되지않아서 메모리 누수가 발생한다. 이를 방지하기 위하여 First class에 소멸자를 가상 소멸자를 사용한다.
    // 그러면 소멸자는 오버라이딩이되서 Third부터 Second, First 순서로 소멸자가 실행되어 모든 메모리가 해제된다.
    delete ptr;

    printf("program end.\n");
}