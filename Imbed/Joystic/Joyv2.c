#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>
#include <pthread.h>
#include <unistd.h>

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

static int lastButtonState[4][4] = { 0 };
char buttonValues[4][4] = {
                {'1', '2', '3', '+'},
                {'4', '5', '6', '-'},
                {'7', '8', '9', 'x'},
                {'*', '0', '#', '/'}
};

void digiInit();
void resetInput();
void displayNumber(int number);
void* displayNumberThread(void* arg);

int main()
{   
    pthread_t tid2;
    int thread_return = 0;

    wiringPiSetupGpio();
    printf("Raspberry Pi SPI ADC Program\n");
    mcp3004Setup(BASE, SPI_CHAN);
    digiInit();

    pinMode(JOY, INPUT);
    pullUpDnControl(JOY, PUD_UP);

    pthread_create(&tid2, NULL, displayNumberThread, NULL);
    printf("thread_id2 : %lu\n", tid2);

    while (1) {

        for (int i = 0; i < 2; i++) {
            currentNumber = analogRead(BASE + i);
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

    pthread_join(tid2, (void**)(&thread_return));
    printf("thread status2 : %d\n", thread_return);
    return 0;
}

void displayNumber(int currentNumber) {
    int digits[4];

    // 숫자를 각 자리수로 분리
    digits[0] = currentNumber / 1000;
    digits[1] = (currentNumber / 100) % 10;
    digits[2] = (currentNumber / 10) % 10;
    digits[3] = currentNumber % 10;

    // 각 자리수를 디스플레이
    for (int cnt = 0; cnt < 40; cnt++) {
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
void* displayNumberThread(void* arg) {
    while (1) {
        displayNumber(currentNumber);
    }
    return NULL;
}
void digiInit() {
    for (int i = 0; i < 4; i++) {
        pinMode(diginum[i], OUTPUT);
        digitalWrite(diginum[i], LOW);
    }

    for (int i = 0; i < 8; i++) {
        pinMode(segnum[i], OUTPUT);
        digitalWrite(segnum[i], HIGH);
    }
}
void resetInput() {
    memset(inputBuffer, 0, sizeof(inputBuffer));
    bufferIndex = 0;
}
