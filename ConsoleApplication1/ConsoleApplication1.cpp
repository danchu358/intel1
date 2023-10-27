#include <iostream>

#define SQUARE(x) ((x) * (x))
#define ABS(x) (((x) < 0) ? -(x) : (x))

int main()
{
    printf("안녕하세요. 환영합니다. C++\n\n");
    printf("2의 제곱 : %d\n", SQUARE(2));
    printf("5의 제곱 : %d\n", SQUARE(5));
    printf("1.2의 제곱 : %f\n", SQUARE(1.2));

    int x = -7;
    printf("%d의 제곱 : %d\n", x ,SQUARE(x));
    printf("%d의 절댓값 : %d\n", x, ABS(x));


}

