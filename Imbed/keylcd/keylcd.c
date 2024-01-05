<<<<<<< HEAD
#include "keylcdV1.h"

int xio;  // I2C 통신을 위한 핸들 또는 파일 디스크립터
int operand1 = 0;  // 전역 변수 정의
int operand2 = 0;
char operator = ' ';
int currentOperand = 1;
int result = 0;

char buttonValues[4][4] = {
                {'1', '2', '3', '+'},
                {'4', '5', '6', '-'},
                {'7', '8', '9', '*'},
                {'C', '0', '=', '/'}
};

void lcd_init(void) {  // LCD 모듈을 초기화하는 함수
    lcd_byte(0x33, LCD_CMD);
    lcd_byte(0x32, LCD_CMD);
    lcd_byte(0x06, LCD_CMD);
    lcd_byte(0x0C, LCD_CMD);
    lcd_byte(0x28, LCD_CMD);
    lcd_byte(0x01, LCD_CMD);
    delayMicroseconds(500);
}
void lcd_byte(int bits, int mode) {  // LCD에 데이터 또는 명령어를 전송하는>
    int bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT;
    int bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT;

    wiringPiI2CReadReg8(xio, bits_high);
    lcd_toggle_enable(bits_high);

    wiringPiI2CReadReg8(xio, bits_low);
    lcd_toggle_enable(bits_low);
}
void lcd_toggle_enable(int bits) {  // LCD의 Enable 신호를 토글하는 함수
    delayMicroseconds(500);
    wiringPiI2CReadReg8(xio, (bits | ENABLE));
    delayMicroseconds(500);
    wiringPiI2CReadReg8(xio, (bits & ~ENABLE));
    delayMicroseconds(500);
}
void lcdLoc(int line) {  // LCD의 커서 위치를 설정하는 함수
    lcd_byte(line, LCD_CMD);
}

void typeln(const char* s) {  // 문자열을 LCD에 출력하는 함수
    while (*s) lcd_byte(*(s++), LCD_CHR);
}
void typeChar(char val) {  // 단일 문자를 LCD에 출력하는 함수
    lcd_byte(val, LCD_CHR);
}

void lcdClear(void) {  // LCD 화면을 지우는 함수
    lcd_byte(0x01, LCD_CMD);
    lcd_byte(0x02, LCD_CMD);
}

void typeInt(int i) {  // 정수를 문자열로 변환하여 LCD에 출력하는 함수
    char array[20];
    sprintf(array, "%d", i);
    typeln(array);
}
void typeFloat(float myFloat) {  // 실수를 문자열로 변환하여 LCD에 출력하는>
    char buffer[20];
    sprintf(buffer, "%4.2f", myFloat);
    typeln(buffer);
}
void processInput(char input) {  // 키패드의 입력된 값을 처리
    char line1[100];

    if (input >= '0' && input <= '9') {
        int number = input - '0';
        if (currentOperand == 1) {
            operand1 = operand1 * 10 + number;
            sprintf(line1, "%d", operand1);
        }
        else if (currentOperand == 2) {
            operand2 = operand2 * 10 + number;
            sprintf(line1, "%d %c %d", operand1, operator, operand2);
        }
        lcdLoc(LINE1);
        typeln(line1);
    }
    else if (input == '+' || input == '-' || input == '*' || input == '/') {
        operator = input;
        sprintf(line1, "%d %c", operand1, operator);
        currentOperand = 2;
        lcdLoc(LINE1);
        typeln(line1);
    }
    else if (input == '=') {
        calcul();
        currentOperand = 1;
    }
    else if (input == 'C') {
        operand1 = 0;
        operand2 = 0;
        operator = ' ';
        currentOperand = 1;
    }
}
void calcul() {
    int result = 0;
    char line1[100];
    char line2[100];

    if (operator == ' ' || operator == '=') {
        result = operand1;
    }
    else {
        switch (operator) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            if (operand2 != 0) {
                result = operand1 / operand2;
            }
            else {
                lcdLoc(LINE1);
                sprintf(line1, "Error: Division by zero\n");
                typeln(line1);
                return;
            }
            break;
        case ' ':
            result = operand1;
            break;
        default:
            //printf("Error: Invalid operation\n");
            return;
        }
    }
    sprintf(line1, "Result: %d %c %d =", operand1, operator, operand2);
    sprintf(line2, "%d", result);

    lcdLoc(LINE1);
    typeln(line1);
    lcdLoc(LINE2);
    typeln(line2);

    // 계산 후 초기화
    operand1 = result;
    operand2 = 0;
    operator = ' ';
    currentOperand = 2;
}
void scanKeys() {
    static int lastButtonState[4][4] = { 0 }; // 모든 버튼의 상태를 0으로 초[>
    int currentButtonState;
    char line1[100];

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

            // 상태 변화가 감지될 경우에만 처리
            if (currentButtonState == LOW && lastButtonState[row][col] == H) {
                lcdClear();
                lcdLoc(LINE1);
                sprintf(line1, "%c\n", buttonValues[row][col]);
                typeln(line1);

                processInput(buttonValues[row][col]);
                delay(200); // 디바운싱 처리
        }

        lastButtonState[row][col] = currentButtonState; // 상태 업데이트
    }
}
}
void setupPins() {
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
=======
#include "keylcdV1.h"

int xio;  // I2C 통신을 위한 핸들 또는 파일 디스크립터
int operand1 = 0;  // 전역 변수 정의
int operand2 = 0;
char operator = ' ';
int currentOperand = 1;
int result = 0;

char buttonValues[4][4] = {
                {'1', '2', '3', '+'},
                {'4', '5', '6', '-'},
                {'7', '8', '9', '*'},
                {'C', '0', '=', '/'}
};

void lcd_init(void) {  // LCD 모듈을 초기화하는 함수
    lcd_byte(0x33, LCD_CMD);
    lcd_byte(0x32, LCD_CMD);
    lcd_byte(0x06, LCD_CMD);
    lcd_byte(0x0C, LCD_CMD);
    lcd_byte(0x28, LCD_CMD);
    lcd_byte(0x01, LCD_CMD);
    delayMicroseconds(500);
}
void lcd_byte(int bits, int mode) {  // LCD에 데이터 또는 명령어를 전송하는>
    int bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT;
    int bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT;

    wiringPiI2CReadReg8(xio, bits_high);
    lcd_toggle_enable(bits_high);

    wiringPiI2CReadReg8(xio, bits_low);
    lcd_toggle_enable(bits_low);
}
void lcd_toggle_enable(int bits) {  // LCD의 Enable 신호를 토글하는 함수
    delayMicroseconds(500);
    wiringPiI2CReadReg8(xio, (bits | ENABLE));
    delayMicroseconds(500);
    wiringPiI2CReadReg8(xio, (bits & ~ENABLE));
    delayMicroseconds(500);
}
void lcdLoc(int line) {  // LCD의 커서 위치를 설정하는 함수
    lcd_byte(line, LCD_CMD);
}

void typeln(const char* s) {  // 문자열을 LCD에 출력하는 함수
    while (*s) lcd_byte(*(s++), LCD_CHR);
}
void typeChar(char val) {  // 단일 문자를 LCD에 출력하는 함수
    lcd_byte(val, LCD_CHR);
}

void lcdClear(void) {  // LCD 화면을 지우는 함수
    lcd_byte(0x01, LCD_CMD);
    lcd_byte(0x02, LCD_CMD);
}

void typeInt(int i) {  // 정수를 문자열로 변환하여 LCD에 출력하는 함수
    char array[20];
    sprintf(array, "%d", i);
    typeln(array);
}
void typeFloat(float myFloat) {  // 실수를 문자열로 변환하여 LCD에 출력하는>
    char buffer[20];
    sprintf(buffer, "%4.2f", myFloat);
    typeln(buffer);
}
void processInput(char input) {  // 키패드의 입력된 값을 처리
    char line1[100];

    if (input >= '0' && input <= '9') {
        int number = input - '0';
        if (currentOperand == 1) {
            operand1 = operand1 * 10 + number;
            sprintf(line1, "%d", operand1);
        }
        else if (currentOperand == 2) {
            operand2 = operand2 * 10 + number;
            sprintf(line1, "%d %c %d", operand1, operator, operand2);
        }
        lcdLoc(LINE1);
        typeln(line1);
    }
    else if (input == '+' || input == '-' || input == '*' || input == '/') {
        operator = input;
        sprintf(line1, "%d %c", operand1, operator);
        currentOperand = 2;
        lcdLoc(LINE1);
        typeln(line1);
    }
    else if (input == '=') {
        calcul();
        currentOperand = 1;
    }
    else if (input == 'C') {
        operand1 = 0;
        operand2 = 0;
        operator = ' ';
        currentOperand = 1;
    }
}
void calcul() {
    int result = 0;
    char line1[100];
    char line2[100];

    if (operator == ' ' || operator == '=') {
        result = operand1;
    }
    else {
        switch (operator) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            if (operand2 != 0) {
                result = operand1 / operand2;
            }
            else {
                lcdLoc(LINE1);
                sprintf(line1, "Error: Division by zero\n");
                typeln(line1);
                return;
            }
            break;
        case ' ':
            result = operand1;
            break;
        default:
            //printf("Error: Invalid operation\n");
            return;
        }
    }
    sprintf(line1, "Result: %d %c %d =", operand1, operator, operand2);
    sprintf(line2, "%d", result);

    lcdLoc(LINE1);
    typeln(line1);
    lcdLoc(LINE2);
    typeln(line2);

    // 계산 후 초기화
    operand1 = result;
    operand2 = 0;
    operator = ' ';
    currentOperand = 2;
}
void scanKeys() {
    static int lastButtonState[4][4] = { 0 }; // 모든 버튼의 상태를 0으로 초[>
    int currentButtonState;
    char line1[100];

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

            // 상태 변화가 감지될 경우에만 처리
            if (currentButtonState == LOW && lastButtonState[row][col] == H) {
                lcdClear();
                lcdLoc(LINE1);
                sprintf(line1, "%c\n", buttonValues[row][col]);
                typeln(line1);

                processInput(buttonValues[row][col]);
                delay(200); // 디바운싱 처리
        }

        lastButtonState[row][col] = currentButtonState; // 상태 업데이트
    }
}
}
void setupPins() {
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
>>>>>>> 6c2513a3afce1b7fe07fe8e435bdf28235ffc650
}