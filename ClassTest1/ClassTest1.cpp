#include <iostream>

class AAA
{
private:
    int a1;
protected:
    int a2;
public:
    int a3;
    AAA() { printf("A\n"); }
    ~AAA() { printf("~A\n"); }

    void name() { printf("this class name = AAA\n"); }
};
class BBB : public AAA
{
public:
    int b1;
    int b2;
    int b3;
    BBB() { printf("B\n"); a3 = 10; }
    ~BBB() { printf("~B\n"); }

    //void Test() { printf("a1 = %d, a2 = %d, a3 = %d\n", a1, a2, a3); }
    void name() { printf("this class name = BBB\n"); }
};
class First
{
public:
    First()
    {
        printf("First\n");
    }
    virtual ~First()
    { 
        printf("~First\n"); }
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

void func()
{
    printf("function start.\n");
    BBB *b = new BBB();
    b->name();

    //((AAA*)b)->name();  // 캐스팅 변수 형태   // 캐스팅 변수 원본 => AAA* a = b; //a->name(); 출력값 : AAA
    
    AAA* a = (AAA*)b;
    a->name();
    printf("a3 = %d\n", ((AAA*)b)->a3);
    delete b;

    printf("function end.\n");
}

void func1()
{
    printf("function start.\n");
    AAA* a = new AAA();
    a->name();

    //((AAA*)b)->name();  // 캐스팅 변수 형태   // 캐스팅 변수 원본 => AAA* a = b; //a->name(); 출력값 : AAA

    BBB* b = (BBB*)a;
    b->name();
    printf("b1 = %d\n", ((BBB*)a)->b1);
    delete a;

    printf("function end.\n");
}

int main()
{
    printf("program start.\n\n");

    First * ptr = new Third();
    delete ptr;

    printf("program end.\n");
}