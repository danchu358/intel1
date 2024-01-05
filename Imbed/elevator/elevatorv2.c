<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <pthread.h>
#include <unistd.h>

#define C4 6
#define C3 13
#define C2 19
#define C1 26
#define R4 12
#define R3 16
#define R2 20
#define R1 21

int R[4] = {21, 20, 16, 12};
int C[4] = { 26, 19, 13, 6 };
//int diginum = {12, 9, 8, 6};
int diginum[5] = { 4, 17, 27, 22 };
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
char buttonValues[4][4] = {
    {'1', '2', '3', '+'},            
    {'4', '5', '6', '-'},            
    {'7', '8', '9', '*'},            
    {'*', '0', '#', '/'}             
};
int digicnt = 4;
int segcnt = 8;
int currentNumber = 0;
//int targetNumber = 0;
int flag_cnt = 0;
static char inputBuffer[11];
static int bufferIndex = 0;

void digiInit();
void setupPins();
void pinModeSet();
void pinPudSet();
void resetInput();
char Keypads();
int toInteger(char input);
void displayNumber(int targetNumber);
void displayNumberCnt(int targetNumber);
void* displayNumberThread(void* arg);
void intIsr(void);

int main()
{
    char input;
    int target;
    int prevTarget = -1;

    pthread_t tid1, tid2;
    int thread_return = 0;

    wiringPiSetupGpio();
    printf("FND 7 Segment Start\n");
    digiInit();
    pinModeSet();
    pinPudSet();

    pthread_create(&tid1, NULL, displayNumberThread, NULL);
    printf("thread_id1 : %lu\n", tid1);

    //for (int i = 0; i < 4; i++) {
    //    wiringPiISR(C[i], INT_EDGE_RISING, &intIsr);
    //}

    while (1) {
        input = Keypads();
        if (input != '\0') {
            target = toInteger(input);
            displayNumberCnt(target);
            //pthread_create(&tid1, NULL, displayNumberThread, NULL);
            //displayNumber(target);
            prevTarget = target;

            //pthread_join(tid1, (void**)(&thread_return));
        }

        //pthread_create(&tid2, NULL, displayNumberCnt, NULL);
        //printf("thread_id2 : %lu\n", tid2);
    
    }

    //pthread_join(tid1, (void**)(&thread_return));
    //printf("thread status : %d\n", thread_return);

    return 0;
}

char Keypads() {
    char input = '\0';

    for (int row = 0; row < 4; ++row) {
        digitalWrite(R1, row == 0 ? LOW : HIGH);
        digitalWrite(R2, row == 1 ? LOW : HIGH);
        digitalWrite(R3, row == 2 ? LOW : HIGH);
        digitalWrite(R4, row == 3 ? LOW : HIGH);

        if (digitalRead(C1) == LOW) {
            printf("%c\n", buttonValues[row][0]);
            input = buttonValues[row][0];
        }
        if (digitalRead(C2) == LOW) {
            printf("%c\n", buttonValues[row][1]);
            input = buttonValues[row][1];
        }
        if (digitalRead(C3) == LOW) {
            printf("%c\n", buttonValues[row][2]);
            input = buttonValues[row][2];
        }
        if (digitalRead(C4) == LOW) {
            printf("%c\n", buttonValues[row][3]);
            input = buttonValues[row][3];
        }

        delay(100);
    }
    return input;
}
int toInteger(char input) {
    int targetNumber = 0;

    if (input >= '0' && input <= '9' && bufferIndex < 10) {
        inputBuffer[bufferIndex++] = input;
    }
    else if (input == '#') {
        inputBuffer[bufferIndex] = '\0';
        targetNumber = atoi(inputBuffer);
        printf("target number : %d\n", targetNumber);
        bufferIndex = 0;
    }

    return targetNumber;
}
void displayNumber(int number) {
    
    int digits[4];

    digits[0] = number / 1000;
    digits[1] = (number / 100) % 10;
    digits[2] = (number / 10) % 10;
    digits[3] = number % 10;

    for (int cnt = 0; cnt < 40; cnt++) {
        for (int i = 0; i < 4; ++i) {

            digitalWrite(diginum[i], HIGH);
            for (int j = 0; j < segcnt; j++) {
                digitalWrite(segnum[j], numlist[digits[i]][j]);
            }
            delay(5);
            digitalWrite(diginum[i], LOW);
        }
    }
}
void displayNumberCnt(int targetNumber) {
    if (currentNumber < targetNumber) {
        for (int i = currentNumber; i <= targetNumber; i++) {
            displayNumber(i);
            currentNumber = i;
        }
    }
    else if (currentNumber > targetNumber) {
        for (int i = currentNumber; i >= targetNumber; i--) {
            displayNumber(i);
            currentNumber = i;
        }
    }
    if (currentNumber == targetNumber) {
        return;
    }
}
/*void displayNumberCnt(int targetNumber) {
    while (1) {
        if (currentNumber < targetNumber) {
            for (int i = currentNumber; i <= targetNumber; i++) {
                displayNumber(i);
                currentNumber = i;
            }
            inputBuffer[0] = '\0';
            resetInput();
        }
        else if (currentNumber > targetNumber) {
            for (int i = currentNumber; i >= targetNumber; i--) {
                displayNumber(i);
                currentNumber = i;
            }
            inputBuffer[0] = '\0';
            resetInput();
        }
        if (currentNumber == targetNumber) break;
    }
}
*/
void displayNumber2(int targetNumber) {

    int digits[4];

    digits[0] = targetNumber / 1000;
    digits[1] = (targetNumber / 100) % 10;
    digits[2] = (targetNumber / 10) % 10;
    digits[3] = targetNumber % 10;

    for (int i = 0; i < 4; ++i) {

        digitalWrite(diginum[i], HIGH);
        for (int j = 0; j < segcnt; j++) {
            digitalWrite(segnum[j], numlist[digits[i]][j]);
        }
        delay(5);
        digitalWrite(diginum[i], LOW);
    }
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
void pinModeSet() {
    for (int i = 0; i < 4; i++) {
        pinMode(R[i], OUTPUT);
        pinMode(C[i], INPUT);
    }
}
void pinPudSet() {
    for (int i = 0; i < 4; i++) {
        pullUpDnControl(C[i], PUD_UP);
    }
}
void* displayNumberThread(void* arg) {
    while (1) {
        displayNumber(currentNumber);
        //if (currentNumber == targetNumber) break;
    }
    return NULL;
}
void intIsr(void) {
    flag_cnt = 1;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <pthread.h>
#include <unistd.h>

#define C4 6
#define C3 13
#define C2 19
#define C1 26
#define R4 12
#define R3 16
#define R2 20
#define R1 21

int R[4] = {21, 20, 16, 12};
int C[4] = { 26, 19, 13, 6 };
//int diginum = {12, 9, 8, 6};
int diginum[5] = { 4, 17, 27, 22 };
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
char buttonValues[4][4] = {
    {'1', '2', '3', '+'},            
    {'4', '5', '6', '-'},            
    {'7', '8', '9', '*'},            
    {'*', '0', '#', '/'}             
};
int digicnt = 4;
int segcnt = 8;
int currentNumber = 0;
//int targetNumber = 0;
int flag_cnt = 0;
static char inputBuffer[11];
static int bufferIndex = 0;

void digiInit();
void setupPins();
void pinModeSet();
void pinPudSet();
void resetInput();
char Keypads();
int toInteger(char input);
void displayNumber(int targetNumber);
void displayNumberCnt(int targetNumber);
void* displayNumberThread(void* arg);
void intIsr(void);

int main()
{
    char input;
    int target;
    int prevTarget = -1;

    pthread_t tid1, tid2;
    int thread_return = 0;

    wiringPiSetupGpio();
    printf("FND 7 Segment Start\n");
    digiInit();
    pinModeSet();
    pinPudSet();

    pthread_create(&tid1, NULL, displayNumberThread, NULL);
    printf("thread_id1 : %lu\n", tid1);

    //for (int i = 0; i < 4; i++) {
    //    wiringPiISR(C[i], INT_EDGE_RISING, &intIsr);
    //}

    while (1) {
        input = Keypads();
        if (input != '\0') {
            target = toInteger(input);
            displayNumberCnt(target);
            //pthread_create(&tid1, NULL, displayNumberThread, NULL);
            //displayNumber(target);
            prevTarget = target;

            //pthread_join(tid1, (void**)(&thread_return));
        }

        //pthread_create(&tid2, NULL, displayNumberCnt, NULL);
        //printf("thread_id2 : %lu\n", tid2);
    
    }

    //pthread_join(tid1, (void**)(&thread_return));
    //printf("thread status : %d\n", thread_return);

    return 0;
}

char Keypads() {
    char input = '\0';

    for (int row = 0; row < 4; ++row) {
        digitalWrite(R1, row == 0 ? LOW : HIGH);
        digitalWrite(R2, row == 1 ? LOW : HIGH);
        digitalWrite(R3, row == 2 ? LOW : HIGH);
        digitalWrite(R4, row == 3 ? LOW : HIGH);

        if (digitalRead(C1) == LOW) {
            printf("%c\n", buttonValues[row][0]);
            input = buttonValues[row][0];
        }
        if (digitalRead(C2) == LOW) {
            printf("%c\n", buttonValues[row][1]);
            input = buttonValues[row][1];
        }
        if (digitalRead(C3) == LOW) {
            printf("%c\n", buttonValues[row][2]);
            input = buttonValues[row][2];
        }
        if (digitalRead(C4) == LOW) {
            printf("%c\n", buttonValues[row][3]);
            input = buttonValues[row][3];
        }

        delay(100);
    }
    return input;
}
int toInteger(char input) {
    int targetNumber = 0;

    if (input >= '0' && input <= '9' && bufferIndex < 10) {
        inputBuffer[bufferIndex++] = input;
    }
    else if (input == '#') {
        inputBuffer[bufferIndex] = '\0';
        targetNumber = atoi(inputBuffer);
        printf("target number : %d\n", targetNumber);
        bufferIndex = 0;
    }

    return targetNumber;
}
void displayNumber(int number) {
    
    int digits[4];

    digits[0] = number / 1000;
    digits[1] = (number / 100) % 10;
    digits[2] = (number / 10) % 10;
    digits[3] = number % 10;

    for (int cnt = 0; cnt < 40; cnt++) {
        for (int i = 0; i < 4; ++i) {

            digitalWrite(diginum[i], HIGH);
            for (int j = 0; j < segcnt; j++) {
                digitalWrite(segnum[j], numlist[digits[i]][j]);
            }
            delay(5);
            digitalWrite(diginum[i], LOW);
        }
    }
}
void displayNumberCnt(int targetNumber) {
    if (currentNumber < targetNumber) {
        for (int i = currentNumber; i <= targetNumber; i++) {
            displayNumber(i);
            currentNumber = i;
        }
    }
    else if (currentNumber > targetNumber) {
        for (int i = currentNumber; i >= targetNumber; i--) {
            displayNumber(i);
            currentNumber = i;
        }
    }
    if (currentNumber == targetNumber) {
        return;
    }
}
/*void displayNumberCnt(int targetNumber) {
    while (1) {
        if (currentNumber < targetNumber) {
            for (int i = currentNumber; i <= targetNumber; i++) {
                displayNumber(i);
                currentNumber = i;
            }
            inputBuffer[0] = '\0';
            resetInput();
        }
        else if (currentNumber > targetNumber) {
            for (int i = currentNumber; i >= targetNumber; i--) {
                displayNumber(i);
                currentNumber = i;
            }
            inputBuffer[0] = '\0';
            resetInput();
        }
        if (currentNumber == targetNumber) break;
    }
}
*/
void displayNumber2(int targetNumber) {

    int digits[4];

    digits[0] = targetNumber / 1000;
    digits[1] = (targetNumber / 100) % 10;
    digits[2] = (targetNumber / 10) % 10;
    digits[3] = targetNumber % 10;

    for (int i = 0; i < 4; ++i) {

        digitalWrite(diginum[i], HIGH);
        for (int j = 0; j < segcnt; j++) {
            digitalWrite(segnum[j], numlist[digits[i]][j]);
        }
        delay(5);
        digitalWrite(diginum[i], LOW);
    }
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
void pinModeSet() {
    for (int i = 0; i < 4; i++) {
        pinMode(R[i], OUTPUT);
        pinMode(C[i], INPUT);
    }
}
void pinPudSet() {
    for (int i = 0; i < 4; i++) {
        pullUpDnControl(C[i], PUD_UP);
    }
}
void* displayNumberThread(void* arg) {
    while (1) {
        displayNumber(currentNumber);
        //if (currentNumber == targetNumber) break;
    }
    return NULL;
}
void intIsr(void) {
    flag_cnt = 1;
}
>>>>>>> 6c2513a3afce1b7fe07fe8e435bdf28235ffc650
