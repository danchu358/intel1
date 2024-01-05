<<<<<<< HEAD
#include "doorlockV2.h"

int xio;  // I2C 통신을 위한 핸들 또는 파일 디스크립터
int number[5] = { '_', '_', '_', '_' };
int i = 0;
int pw[5] = { '0', '0', '0', '0' };
int newpw[5];
char star[4] = { '_', '_', '_', '_' };
static int lastButtonState[4][4] = { 0 };
char lastButtonPressed;
int current = 0;

char buttonValues[4][4] = {
                {'1', '2', '3', '+'},
                {'4', '5', '6', '-'},
                {'7', '8', '9', 'x'},
                {'*', '0', '#', '/'}
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
void processInput(char input) {
    char line1[100];
    int num;

    if (current == 0) {
        if (input >= '0' && input <= '9') {
            if (i < 4) {
                num = input - '0';
                number[i] = num;
                star[i] = '*';

                lcdClear();
                lcdLoc(LINE1);
                sprintf(line1, "%c %c %c %c", star[0], star[1], star[2], star[3]);
                typeln(line1);

                i++;
            }
        }
        else if (input == '*') {
            compare();
        }
        else if (input == '#') {
            current = 1;
            lcdClear();
            lcdLoc(LINE1);
            sprintf(line1, "Change PW");
            typeln(line1);
        }
    }
    else if(current == 1){
        if (input >= '0' && input <= '9') {
            num = input - '0';
            newpw[i] = num;
            pw[i] = newpw[i];
            star[i] = '*';

            lcdClear();
            lcdLoc(LINE1);
            sprintf(line1, "%c %c %c %c", star[0], star[1], star[2], star[3]);
            typeln(line1);

            i++;
        }
        else if (input == '*') {
            lcdClear();
            lcdLoc(LINE1);
            sprintf(line1, "Save");
            typeln(line1);
            current = 0;

            digitalWrite(LED, HIGH);
            delay(100);

            for (int j = 0; j < 4; j++) {
                number[j] = 0;
            }
            for (int j = 0; j < 4; j++) {
                star[j] = '_'
            }
            i = 0;
        }
    }
}
void compare() {
    char line1[100];

    if (pw[0] == number[0] && pw[1] == number[1] && pw[2] == number[2] && pw[3] == number[3]) {
        lcdClear();
        lcdLoc(LINE1);
        sprintf(line1, "open");
        typeln(line1);

        digitalWrite(LED, HIGH);
        delay(100);
    }
    else {
        lcdClear();
        lcdLoc(LINE1);
        sprintf(line1, "retry");
        typeln(line1);

        digitalWrite(LED, LOW);
        delay(100);
    }

    for (j = 0; j < 4; j++) {
        number[j] = 0;
    }
    for (j = 0; j < 4; j++) {
        star[j] = '_';
    }

    i = 0;
}
void scanKeys() {
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
            if (currentButtonState == LOW && lastButtonState[row][col] == HIGH) {
                lcdClear();
                lcdLoc(LINE1);
                sprintf(line1, "%c\n", buttonValues[row][col]);
                typeln(line1);

                processInput(buttonValues[row][col]);
                delay(200);
            }
            lastButtonState[row][col] = currentButtonState;
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
#include "doorlockV2.h"

int xio;  // I2C 통신을 위한 핸들 또는 파일 디스크립터
int number[5] = { '_', '_', '_', '_' };
int i = 0;
int pw[5] = { '0', '0', '0', '0' };
int newpw[5];
char star[4] = { '_', '_', '_', '_' };
static int lastButtonState[4][4] = { 0 };
char lastButtonPressed;
int current = 0;

char buttonValues[4][4] = {
                {'1', '2', '3', '+'},
                {'4', '5', '6', '-'},
                {'7', '8', '9', 'x'},
                {'*', '0', '#', '/'}
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
void processInput(char input) {
    char line1[100];
    int num;

    if (current == 0) {
        if (input >= '0' && input <= '9') {
            if (i < 4) {
                num = input - '0';
                number[i] = num;
                star[i] = '*';

                lcdClear();
                lcdLoc(LINE1);
                sprintf(line1, "%c %c %c %c", star[0], star[1], star[2], star[3]);
                typeln(line1);

                i++;
            }
        }
        else if (input == '*') {
            compare();
        }
        else if (input == '#') {
            current = 1;
            lcdClear();
            lcdLoc(LINE1);
            sprintf(line1, "Change PW");
            typeln(line1);
        }
    }
    else if(current == 1){
        if (input >= '0' && input <= '9') {
            num = input - '0';
            newpw[i] = num;
            pw[i] = newpw[i];
            star[i] = '*';

            lcdClear();
            lcdLoc(LINE1);
            sprintf(line1, "%c %c %c %c", star[0], star[1], star[2], star[3]);
            typeln(line1);

            i++;
        }
        else if (input == '*') {
            lcdClear();
            lcdLoc(LINE1);
            sprintf(line1, "Save");
            typeln(line1);
            current = 0;

            digitalWrite(LED, HIGH);
            delay(100);

            for (int j = 0; j < 4; j++) {
                number[j] = 0;
            }
            for (int j = 0; j < 4; j++) {
                star[j] = '_'
            }
            i = 0;
        }
    }
}
void compare() {
    char line1[100];

    if (pw[0] == number[0] && pw[1] == number[1] && pw[2] == number[2] && pw[3] == number[3]) {
        lcdClear();
        lcdLoc(LINE1);
        sprintf(line1, "open");
        typeln(line1);

        digitalWrite(LED, HIGH);
        delay(100);
    }
    else {
        lcdClear();
        lcdLoc(LINE1);
        sprintf(line1, "retry");
        typeln(line1);

        digitalWrite(LED, LOW);
        delay(100);
    }

    for (j = 0; j < 4; j++) {
        number[j] = 0;
    }
    for (j = 0; j < 4; j++) {
        star[j] = '_';
    }

    i = 0;
}
void scanKeys() {
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
            if (currentButtonState == LOW && lastButtonState[row][col] == HIGH) {
                lcdClear();
                lcdLoc(LINE1);
                sprintf(line1, "%c\n", buttonValues[row][col]);
                typeln(line1);

                processInput(buttonValues[row][col]);
                delay(200);
            }
            lastButtonState[row][col] = currentButtonState;
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