#include "fnd_v5.h"

int xio;  // I2C ����� ���� �ڵ� �Ǵ� ���� ��ũ����
int current = 0;

static int lastButtonState[4][4] = { 0 };
char buttonValues[4][4] = {
                {'1', '2', '3', '+'},
                {'4', '5', '6', '-'},
                {'7', '8', '9', 'x'},
                {'*', '0', '#', '/'}
};

int digicnt = 4;
int segcnt = 8;
int nums = 17;
int diginum[5] = { 4, 17, 27, 22 }; // ��������� ��ȣ
int segnum[9] = { 5, 7, 8, 25, 24, 23, 15, 14 }; // ��������� ��ȣ

// ���� ����� ���� �迭
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
    {0, 0, 0, 1, 0, 0, 0, 0},   //A
    {1, 1, 0, 0, 0, 0, 0, 0},   //B
    {0, 1, 1, 0, 0, 0, 1, 0},   //C
    {1, 0, 0, 0, 0, 1, 0, 0},   //D
    {0, 1, 1, 0, 0, 0, 0, 0},   //E
    {0, 1, 1, 1, 0, 0, 0, 0},   //F
    {0, 0, 0, 0, 0, 0, 0, 1}    //X
};

void digiOff() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(diginum[i], LOW);
    }
}
void segOff() {
    for (int i = 0; i < 8; i++) {
        digitalWrite(segnum[i], HIGH);
    }
}
void lcd_init(void) {  // LCD ����� �ʱ�ȭ�ϴ� �Լ�
    lcd_byte(0x33, LCD_CMD);
    lcd_byte(0x32, LCD_CMD);
    lcd_byte(0x06, LCD_CMD);
    lcd_byte(0x0C, LCD_CMD);
    lcd_byte(0x28, LCD_CMD);
    lcd_byte(0x01, LCD_CMD);
    delayMicroseconds(500);
}
void lcd_byte(int bits, int mode) {  // LCD�� ������ �Ǵ� ��ɾ �����ϴ�>
    int bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT;
    int bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT;

    wiringPiI2CReadReg8(xio, bits_high);
    lcd_toggle_enable(bits_high);

    wiringPiI2CReadReg8(xio, bits_low);
    lcd_toggle_enable(bits_low);
}
void lcd_toggle_enable(int bits) {  // LCD�� Enable ��ȣ�� ����ϴ� �Լ�
    delayMicroseconds(500);
    wiringPiI2CReadReg8(xio, (bits | ENABLE));
    delayMicroseconds(500);
    wiringPiI2CReadReg8(xio, (bits & ~ENABLE));
    delayMicroseconds(500);
}
void lcdLoc(int line) {  // LCD�� Ŀ�� ��ġ�� �����ϴ� �Լ�
    lcd_byte(line, LCD_CMD);
}

void typeln(const char* s) {  // ���ڿ��� LCD�� ����ϴ� �Լ�
    while (*s) lcd_byte(*(s++), LCD_CHR);
}
void typeChar(char val) {  // ���� ���ڸ� LCD�� ����ϴ� �Լ�
    lcd_byte(val, LCD_CHR);
}

void lcdClear(void) {  // LCD ȭ���� ����� �Լ�
    lcd_byte(0x01, LCD_CMD);
    lcd_byte(0x02, LCD_CMD);
}

void typeInt(int i) {  // ������ ���ڿ��� ��ȯ�Ͽ� LCD�� ����ϴ� �Լ�
    char array[20];
    sprintf(array, "%d", i);
    typeln(array);
}
void typeFloat(float myFloat) {  // �Ǽ��� ���ڿ��� ��ȯ�Ͽ� LCD�� ����ϴ�>
    char buffer[20];
    sprintf(buffer, "%4.2f", myFloat);
    typeln(buffer);
}
void processInput(char* input) {

    digiOff();
    segOff();

    while (1) {
        switch (*input)
        {
        case '0':
            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[0][i]);
            }
            delay(500);
            digiOff();
            segOff();

            break;
        case '3':            
            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[0][i]);
            }
            delay(500);
            digiOff();
            segOff();
 
            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[1][i]);
            }
            delay(500);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[2][i]);
            }
            delay(500);
            digiOff();
            segOff();
            
            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
            digitalWrite(segnum[i], numlist[3][i]);
            }
            delay(500);

            break;

        case '10':
            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[0][i]);
            }
            delay(500);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[1][i]);
            }
            delay(500);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[2][i]);
            }
            delay(500);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[3][i]);
            }
            delay(500);

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[4][i]);
            }
            delay(500);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[5][i]);
            }
            delay(500);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[6][i]);
            }
            delay(500);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[7][i]);
            }
            delay(500);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[8][i]);
            }
            delay(500);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[9][i]);
            }
            delay(500);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[1][i]);
            }
            delay(500);
            digiOff();
            segOff();

            digitalWrite(diginum[1], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[0][i]);
            }
            delay(500);
            digiOff();
            segOff();

            break;

        default:
            break;
        }
        /*
        if (*input == '0') {
            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i],numlist[0][i]);
            }
            delay(1);
            digiOff();
            segOff();
        }
        if (*input == '3') {
            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[0][i]);
            }
            delay(1);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[1][i]);
            }
            delay(1);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[2][i]);
            }
            delay(1);
            digiOff();
            segOff();

            digitalWrite(diginum[0], HIGH);
            for (int i = 0; i < 8; i++) {
                digitalWrite(segnum[i], numlist[3][i]);
            }
            delay(1);
            digiOff();
            segOff();
        }
    }*/
    //showNum(*input);
}
void scanKeys() {
    int currentButtonState;
    char line1[100];
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

            // ���� ��ȭ�� ������ ��쿡�� ó��
            if (currentButtonState == LOW && lastButtonState[row][col] == HIGH) {
                input = buttonValues[row][col];
                lcdClear();
                lcdLoc(LINE1);
                sprintf(line1, "%c\n", input);
                typeln(line1);

                processInput(&input);
                delay(200);
            }
            lastButtonState[row][col] = currentButtonState;
        }
    }
}
void setupPins() {
    // ���� ������� ����
    pinMode(R1, OUTPUT);
    pinMode(R2, OUTPUT);
    pinMode(R3, OUTPUT);
    pinMode(R4, OUTPUT);

    // ���� �Է����� ����
    pinMode(C1, INPUT);
    pinMode(C2, INPUT);
    pinMode(C3, INPUT);
    pinMode(C4, INPUT);

    // ���� Ǯ�� ���� Ȱ��ȭ
    pullUpDnControl(C1, PUD_UP);
    pullUpDnControl(C2, PUD_UP);
    pullUpDnControl(C3, PUD_UP);
    pullUpDnControl(C4, PUD_UP);
}
void showNum() {
    if (*input == 0) {
        digitalWrite(diginum[0], HIGH);
        for (int i = 0; i < 8; i++) {
            numlist[0][i];
        }        
        delay(1);
        digiOff();
        segOff();

        digitalWrite(diginum[1], HIGH);
        for (int i = 0; i < 8; i++) {
            numlist[1][i];
        }
        delay(1);
        digiOff();
        segOff();

        digitalWrite(diginum[2], HIGH);
        for (int i = 0; i < 8; i++) {
            numlist[2][i];
        }
        delay(1);
        digiOff();
        segOff();

        digitalWrite(diginum[3], HIGH);
        for (int i = 0; i < 8; i++) {
            numlist[3][i];
        }
        delay(1);
        digiOff();
        segOff();
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