<<<<<<< HEAD
#pragma once
// 헤더파일
#include <stdio.h>
#include <stdlib.h>
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
extern int operand1;
extern int operand2;
extern char operator;
extern int currentOperand;
extern char buttonValues[4][4];

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
=======
#pragma once
// 헤더파일
#include <stdio.h>
#include <stdlib.h>
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
extern int operand1;
extern int operand2;
extern char operator;
extern int currentOperand;
extern char buttonValues[4][4];

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
>>>>>>> 6c2513a3afce1b7fe07fe8e435bdf28235ffc650
void processInput(char input);