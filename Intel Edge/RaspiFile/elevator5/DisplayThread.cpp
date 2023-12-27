#include "DisplayThread.h"

//int diginum = {12, 9, 8, 6};
int diginum[4] = {4, 17, 27, 22};
//int segnum = {11, 7, 4, 2, 1, 10, 5, 3};
int segnum[8] = { 5, 7, 8, 25, 24, 23, 15, 14 };
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

int lastButtonState[4][4] = { 0 };
char buttonValues[4][4] = {
                {'1', '2', '3', '+'},
                {'4', '5', '6', '-'},
                {'7', '8', '9', 'x'},
                {'*', '0', '#', '/'}
};

DisplayThread::DisplayThread(QObject *parent)
    : QThread(parent), currentNumber(0) {}

void DisplayThread::run() {
    while (true) {
        int digits[4];
        {
            QMutexLocker locker(&mutex);
            // 숫자를 각 자리수로 분리
            digits[0] = currentNumber / 1000;
            digits[1] = (currentNumber / 100) % 10;
            digits[2] = (currentNumber / 10) % 10;
            digits[3] = currentNumber % 10;
        }

        for (int i = 0; i < 4; ++i) {
            digiInit();
            digitalWrite(diginum[i], HIGH);
            for (int j = 0; j < segcnt; j++) {
                digitalWrite(segnum[j], numlist[digits[i]][j]);
            }
            delay(3);
            digitalWrite(diginum[i], LOW);
        }

        {
            QMutexLocker locker(&mutex);
            emit updateDisplay(currentNumber);
        }
    }
}
void DisplayThread::setNumber(int number) {
    QMutexLocker locker(&mutex);
    currentNumber = number;

    // 디스플레이 값을 설정하는 코드 추가
    int digits[4];
    // 숫자를 각 자리수로 분리
    digits[0] = currentNumber / 1000;
    digits[1] = (currentNumber / 100) % 10;
    digits[2] = (currentNumber / 10) % 10;
    digits[3] = currentNumber % 10;

    for (int i = 0; i < 4; ++i) {
        digiInit();
        digitalWrite(diginum[i], HIGH);
        for (int j = 0; j < segcnt; j++) {
            digitalWrite(segnum[j], numlist[digits[i]][j]);
        }
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
