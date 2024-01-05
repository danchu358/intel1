<<<<<<< HEAD
#include "doorlockV2.h"

int main()
{
    wiringPiSetupGpio();
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    xio = wiringPiI2CSetup(I2C_ADDR);

    char line1[100];

    lcd_init();

    setupPins();

    printf("Rasberry Pi Start\n");
    printf("push the button\n");

    lcdClear();
    lcdLoc(LINE1);
    sprintf(line1, "Start");
    typeln(line1);

    while (1) {
        delay(50);
        scanKeys();
    }
    return 0;
=======
#include "doorlockV2.h"

int main()
{
    wiringPiSetupGpio();
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    xio = wiringPiI2CSetup(I2C_ADDR);

    char line1[100];

    lcd_init();

    setupPins();

    printf("Rasberry Pi Start\n");
    printf("push the button\n");

    lcdClear();
    lcdLoc(LINE1);
    sprintf(line1, "Start");
    typeln(line1);

    while (1) {
        delay(50);
        scanKeys();
    }
    return 0;
>>>>>>> 6c2513a3afce1b7fe07fe8e435bdf28235ffc650
}