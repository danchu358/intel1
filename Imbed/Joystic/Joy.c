<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

// SPI 통신
#define BASE 100
#define SPI_CHAN 0

// JOY
#define JOY 18

//int diginum = {12, 9, 8, 6};
int diginum[5] = { 4, 17, 27, 22 };
//int segnum = {11, 7, 4, 2, 1, 10, 5, 3};
int segnum[9] = { 5, 7, 0, 25, 24, 23, 15, 14 };
int numlist[17][9] = {
    {0, 0, 0, 0, 0, 0, 1, 0},   //0
    {1, 0, 0, 1, 1, 1, 1, 0},   //1
    {0, 0, 1, 0, 0, 1, 0, 0},   //2
    {0, 0, 0, 0, 1, 1, 0, 0},   //3
    {1, 0, 0, 1, 1, 0, 0, 0},   //4
    {0, 1, 0, 0, 1, 0, 0, 0},   //5
    {0, 1, 0, 0, 0, 0, 0, 0},   //6
    {0, 0, 0, 1, 1, 0, 1, 0},   //7
    {0, 0, 0, 0, 0, 0, 0, 0},   //8
    {0, 0, 0, 0, 1, 0, 0, 0},   //9
};
int digicnt = 4;
int segcnt = 8;
char inputBuffer[11];
int bufferIndex = 0;
int displayValue = 0;
int currentNumber = 0;

void digiInit();
void resetInput();
void displayNumber(int number);
void displayNumber2(int number);

static int lastButtonState[4][4] = { 0 };
char buttonValues[4][4] = {
                {'1', '2', '3', '+'},
                {'4', '5', '6', '-'},
                {'7', '8', '9', 'x'},
                {'*', '0', '#', '/'}
};

int main()
{
    wiringPiSetupGpio();
    printf("Raspberry Pi SPI ADC Program\n");
    mcp3004Setup(BASE, SPI_CHAN);
    digiInit();

    pinMode(JOY, INPUT);
    pullUpDnControl(JOY, PUD_UP);

    while (1) {

        displayNumber2(currentNumber);

        for (int i = 0; i < 2; i++) {
            int currentNumber = analogRead(BASE + i);
            printf("channel%d value:%4d\t", i, analogRead(BASE + i));
            displayNumber(currentNumber);
            delay(200);
        }
        printf("\n");

        if (digitalRead(JOY) == LOW) {
            printf("On\n");
        }
        else {
            printf("Off\n");
        }
    }
    return 0;
}

void displayNumber(int number) {
    int digits[4];

    // 숫자를 각 자리수로 분리
    digits[0] = number / 1000;
    digits[1] = (number / 100) % 10;
    digits[2] = (number / 10) % 10;
    digits[3] = number % 10;

    // 각 자리수를 디스플레이
    for (int cnt = 0; cnt < 10; cnt++) {
        for (int i = 0; i < 4; ++i) {
            digiInit();

            // 해당 자리수만 켜기
            digitalWrite(diginum[i], HIGH);
            for (int j = 0; j < segcnt; j++) {
                digitalWrite(segnum[j], numlist[digits[i]][j]);
            }
            delay(5);
            digitalWrite(diginum[i], LOW);
        }
    }
}
void displayNumber2(int number) {
    int digits[4];

    // 숫자를 각 자리수로 분리
    digits[0] = number / 1000;
    digits[1] = (number / 100) % 10;
    digits[2] = (number / 10) % 10;
    digits[3] = number % 10;

    // 각 자리수를 디스플레이
    for (int i = 0; i < 4; ++i) {
        digiInit();

        // 해당 자리수만 켜기
        digitalWrite(diginum[i], HIGH);
        for (int j = 0; j < segcnt; j++) {
            digitalWrite(segnum[j], numlist[digits[i]][j]);
        }
        delay(5);
        digitalWrite(diginum[i], LOW);
    }
}
void digiInit() {
    pinMode(diginum[0], OUTPUT);
    pinMode(diginum[1], OUTPUT);
    pinMode(diginum[2], OUTPUT);
    pinMode(diginum[3], OUTPUT);

    pinMode(segnum[0], OUTPUT);
    pinMode(segnum[1], OUTPUT);
    pinMode(segnum[2], OUTPUT);
    pinMode(segnum[3], OUTPUT);
    pinMode(segnum[4], OUTPUT);
    pinMode(segnum[5], OUTPUT);
    pinMode(segnum[6], OUTPUT);
    pinMode(segnum[7], OUTPUT);

    digitalWrite(diginum[0], LOW);
    digitalWrite(diginum[1], LOW);
    digitalWrite(diginum[2], LOW);
    digitalWrite(diginum[3], LOW);

    digitalWrite(segnum[0], HIGH);
    digitalWrite(segnum[1], HIGH);
    digitalWrite(segnum[2], HIGH);
    digitalWrite(segnum[3], HIGH);
    digitalWrite(segnum[4], HIGH);
    digitalWrite(segnum[5], HIGH);
    digitalWrite(segnum[6], HIGH);
    digitalWrite(segnum[7], HIGH);
}
void resetInput() {
    memset(inputBuffer, 0, sizeof(inputBuffer));
    bufferIndex = 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

// SPI 통신
#define BASE 100
#define SPI_CHAN 0

// JOY
#define JOY 18

//int diginum = {12, 9, 8, 6};
int diginum[5] = { 4, 17, 27, 22 };
//int segnum = {11, 7, 4, 2, 1, 10, 5, 3};
int segnum[9] = { 5, 7, 0, 25, 24, 23, 15, 14 };
int numlist[17][9] = {
    {0, 0, 0, 0, 0, 0, 1, 0},   //0
    {1, 0, 0, 1, 1, 1, 1, 0},   //1
    {0, 0, 1, 0, 0, 1, 0, 0},   //2
    {0, 0, 0, 0, 1, 1, 0, 0},   //3
    {1, 0, 0, 1, 1, 0, 0, 0},   //4
    {0, 1, 0, 0, 1, 0, 0, 0},   //5
    {0, 1, 0, 0, 0, 0, 0, 0},   //6
    {0, 0, 0, 1, 1, 0, 1, 0},   //7
    {0, 0, 0, 0, 0, 0, 0, 0},   //8
    {0, 0, 0, 0, 1, 0, 0, 0},   //9
};
int digicnt = 4;
int segcnt = 8;
char inputBuffer[11];
int bufferIndex = 0;
int displayValue = 0;
int currentNumber = 0;

void digiInit();
void resetInput();
void displayNumber(int number);
void displayNumber2(int number);

static int lastButtonState[4][4] = { 0 };
char buttonValues[4][4] = {
                {'1', '2', '3', '+'},
                {'4', '5', '6', '-'},
                {'7', '8', '9', 'x'},
                {'*', '0', '#', '/'}
};

int main()
{
    wiringPiSetupGpio();
    printf("Raspberry Pi SPI ADC Program\n");
    mcp3004Setup(BASE, SPI_CHAN);
    digiInit();

    pinMode(JOY, INPUT);
    pullUpDnControl(JOY, PUD_UP);

    while (1) {

        displayNumber2(currentNumber);

        for (int i = 0; i < 2; i++) {
            int currentNumber = analogRead(BASE + i);
            printf("channel%d value:%4d\t", i, analogRead(BASE + i));
            displayNumber(currentNumber);
            delay(200);
        }
        printf("\n");

        if (digitalRead(JOY) == LOW) {
            printf("On\n");
        }
        else {
            printf("Off\n");
        }
    }
    return 0;
}

void displayNumber(int number) {
    int digits[4];

    // 숫자를 각 자리수로 분리
    digits[0] = number / 1000;
    digits[1] = (number / 100) % 10;
    digits[2] = (number / 10) % 10;
    digits[3] = number % 10;

    // 각 자리수를 디스플레이
    for (int cnt = 0; cnt < 10; cnt++) {
        for (int i = 0; i < 4; ++i) {
            digiInit();

            // 해당 자리수만 켜기
            digitalWrite(diginum[i], HIGH);
            for (int j = 0; j < segcnt; j++) {
                digitalWrite(segnum[j], numlist[digits[i]][j]);
            }
            delay(5);
            digitalWrite(diginum[i], LOW);
        }
    }
}
void displayNumber2(int number) {
    int digits[4];

    // 숫자를 각 자리수로 분리
    digits[0] = number / 1000;
    digits[1] = (number / 100) % 10;
    digits[2] = (number / 10) % 10;
    digits[3] = number % 10;

    // 각 자리수를 디스플레이
    for (int i = 0; i < 4; ++i) {
        digiInit();

        // 해당 자리수만 켜기
        digitalWrite(diginum[i], HIGH);
        for (int j = 0; j < segcnt; j++) {
            digitalWrite(segnum[j], numlist[digits[i]][j]);
        }
        delay(5);
        digitalWrite(diginum[i], LOW);
    }
}
void digiInit() {
    pinMode(diginum[0], OUTPUT);
    pinMode(diginum[1], OUTPUT);
    pinMode(diginum[2], OUTPUT);
    pinMode(diginum[3], OUTPUT);

    pinMode(segnum[0], OUTPUT);
    pinMode(segnum[1], OUTPUT);
    pinMode(segnum[2], OUTPUT);
    pinMode(segnum[3], OUTPUT);
    pinMode(segnum[4], OUTPUT);
    pinMode(segnum[5], OUTPUT);
    pinMode(segnum[6], OUTPUT);
    pinMode(segnum[7], OUTPUT);

    digitalWrite(diginum[0], LOW);
    digitalWrite(diginum[1], LOW);
    digitalWrite(diginum[2], LOW);
    digitalWrite(diginum[3], LOW);

    digitalWrite(segnum[0], HIGH);
    digitalWrite(segnum[1], HIGH);
    digitalWrite(segnum[2], HIGH);
    digitalWrite(segnum[3], HIGH);
    digitalWrite(segnum[4], HIGH);
    digitalWrite(segnum[5], HIGH);
    digitalWrite(segnum[6], HIGH);
    digitalWrite(segnum[7], HIGH);
}
void resetInput() {
    memset(inputBuffer, 0, sizeof(inputBuffer));
    bufferIndex = 0;
}
>>>>>>> 6c2513a3afce1b7fe07fe8e435bdf28235ffc650
