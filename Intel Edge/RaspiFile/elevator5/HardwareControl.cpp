#include "HardwareControl.h"
#include "elevatorPanel.h"

//int diginum = {12, 9, 8, 6};
int diginum[5] = {4, 17, 27, 22};
//int segnum = {11, 7, 4, 2, 1, 10, 5, 3};
int segnum[9] = { 5, 7, 8, 25, 24, 23, 15, 14 };
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

void HardwareControl::scanKeys() {
    int currentButtonState;
    char input;

    for (int row = 0; row < 4; ++row) {
        digitalWrite(R1, row == 0 ? LOW : HIGH);
        digitalWrite(R2, row == 1 ? LOW : HIGH);
        digitalWrite(R3, row == 2 ? LOW : HIGH);
        digitalWrite(R4, row == 3 ? LOW : HIGH);

        for (int col = 0; col < 4; ++col) {
            switch (col) {
            case 0: currentButtonState = digitalRead(C1); break;
            case 1: currentButtonState = digitalRead(C2); break;
            case 2: currentButtonState = digitalRead(C3); break;
            case 3: currentButtonState = digitalRead(C4); break;
            }

            if (currentButtonState == LOW && lastButtonState[row][col] == HIGH) {
                delay(100);
                input = buttonValues[row][col];
                qDebug() << "Button pressed:" << input;
                //ui->label->setText(QString("현재숫자: %1").arg(input));

                if (input >= '0' && input <= '9' && bufferIndex < 10) {
                    inputBuffer[bufferIndex++] = input;
                } else if (input == '#') {
                    inputBuffer[bufferIndex] = '\0';
                    int targetNumber = atoi(inputBuffer);

                    if (currentNumber < targetNumber) {
                        for (int i = currentNumber; i <= targetNumber; i++) {
                            //displayNumber();
                            currentNumber = i;
                            //delay(1000);
                        }
                        memset(inputBuffer, 0, sizeof(inputBuffer));
                        bufferIndex = 0;
                    } else {
                        for (int i = currentNumber; i >= targetNumber; i--) {
                            //displayNumber();
                            currentNumber = i;
                            //delay(1000);
                        }
                        memset(inputBuffer, 0, sizeof(inputBuffer));
                        bufferIndex = 0;
                    }
                }
            }
            lastButtonState[row][col] = currentButtonState;
        }
    }
}
void HardwareControl::displayNumber() {
    int digits[4];

    digits[0] = currentNumber / 1000;
    digits[1] = (currentNumber / 100) % 10;
    digits[2] = (currentNumber / 10) % 10;
    digits[3] = currentNumber % 10;

    for (int cnt = 0; cnt < 10; cnt++) {
        for (int i = 0; i < 4; ++i) {
            digiInit();

            digitalWrite(diginum[i], HIGH);
            for (int j = 0; j < segcnt; j++) {
                digitalWrite(segnum[j], numlist[digits[i]][j]);
            }
            delay(5);
            digitalWrite(diginum[i], LOW);
        }
    }
}
void HardwareControl::digiInit() {
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
void HardwareControl::setupPins() {
    // 행을 출력으로 설정
    pinMode(R1, OUTPUT);
    pinMode(R2, OUTPUT);
    pinMode(R3, OUTPUT);
    pinMode(R4, OUTPUT);

    // 열을 입력으로 설정
    pinMode(C1, INPUT);
    pinMode(C2, INPUT);
    pinMode(C3, INPUT);
    pinMode(C4, INPUT);

    // 내부 풀업 저항 활성화
    pullUpDnControl(C1, PUD_UP);
    pullUpDnControl(C2, PUD_UP);
    pullUpDnControl(C3, PUD_UP);
    pullUpDnControl(C4, PUD_UP);
}
