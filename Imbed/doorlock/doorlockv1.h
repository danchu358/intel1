// 헤더파일
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

// LCD
#define I2C_ADDR 0x27    // I2C 주소 설정
#define LCD_CHR 1
#define LCD_CMD 0
#define LINE1 0x80
#define LINE2 0xC0
#define LCD_BACKLIGHT 0x08
#define ENABLE 0x04
#define LED 24

// Keypad
#define C4 6
#define C3 13
#define C2 19
#define C1 26
#define R4 12
#define R3 16
#define R2 20
#define R1 21

extern int xio;
extern char buttonValues[4][4];
extern int number[5];
extern int i;
extern int pw[5];
extern char star[4];
extern static int lastButtonState[4][4];

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);
void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line);
void lcdClear(void);
void typeln(const char* s);
void typeChar(char val);
void scanKeys();
void setupPins();
void calcul();
void processInput(char input);
void compare();
void number_init();
void changepw();
void changepwinput();