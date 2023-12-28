#include ""adc_v1.h"

int xio;  // I2C ����� ���� �ڵ� �Ǵ� ���� ��ũ����
int lastButtonState[4][4] = { 0 };
char buttonValues[4][4] = {
                {'1', '2', '3', '+'},
                {'4', '5', '6', '-'},
                {'7', '8', '9', 'x'},
                {'*', '0', '#', '/'}
};
const int pinLed = 17;

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
    char line1[100];
    int num, cnt;

    if (*input == '0') {
        lcdClear();
        lcdLoc(LINE1);
        printf("PWM Start\n");
        sprintf(line1, "PWM Start");
        typeln(line1);

        while (*input == '0') {
            for (int cnt = 0; cnt < 200; cnt++) {
                softPwmWrite(pinLed, cnt);
                delay(20);
            }
            for (int cnt = 200; cnt > 0; cnt--) {
                softPwmWrite(pinLed, cnt);
                delay(20);
            }
        }
    }
    if (*input == '1') {
        lcdClear();
        lcdLoc(LINE1);
        printf("CDS Start\n");
        sprintf(line1, "CDS Start");
        typeln(line1);

        while (*input == '1') {
            lcdClear();
            lcdLoc(LINE1);
            printf("CDS : %d\n", analogRead(BASE + SPI_CHAN));
            sprintf(line1, "CDS : %d\n", analogRead(BASE + SPI_CHAN));
            typeln(line1);
            delay(300);
        }
    }
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
                printf("%c\n", input);
                sprintf(line1, "%c", input);
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
