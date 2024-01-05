<<<<<<< HEAD
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

// SPI 통신
#define BASE 100
#define SPI_CHAN 0

// LCD
#define I2C_ADDR 0x27    // I2C 주소 설정
#define LCD_CHR 1
#define LCD_CMD 0
#define LINE1 0x80
#define LINE2 0xC0
#define LCD_BACKLIGHT 0x08
#define ENABLE 0x04

// LED
#define LED 17

// Keypad
#define C4 6
#define C3 13
#define C2 19
#define C1 26
#define R4 12
#define R3 16
#define R2 20
#define R1 21

// 변수 설정
extern int xio;
extern char buttonValues[4][4];
extern int lastButtonState[4][4];
extern const int pinLed;

// 함수 선언
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
void processInput(char input);
=======
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

// SPI 통신
#define BASE 100
#define SPI_CHAN 0

// LCD
#define I2C_ADDR 0x27    // I2C 주소 설정
#define LCD_CHR 1
#define LCD_CMD 0
#define LINE1 0x80
#define LINE2 0xC0
#define LCD_BACKLIGHT 0x08
#define ENABLE 0x04

// LED
#define LED 17

// Keypad
#define C4 6
#define C3 13
#define C2 19
#define C1 26
#define R4 12
#define R3 16
#define R2 20
#define R1 21

// 변수 설정
extern int xio;
extern char buttonValues[4][4];
extern int lastButtonState[4][4];
extern const int pinLed;

// 함수 선언
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
void processInput(char input);
>>>>>>> 6c2513a3afce1b7fe07fe8e435bdf28235ffc650
