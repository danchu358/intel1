<<<<<<< HEAD
#include "keylcdV1.h"

int main()
{
    wiringPiSetupGpio();
    xio = wiringPiI2CSetup(I2C_ADDR);
    lcd_init();

    setupPins();

    printf("Rasberry Pi Start\n");
    printf("push the button\n");

    while (1) {
        delay(50);
        scanKeys();
    }
    return 0;
=======
#include "keylcdV1.h"

int main()
{
    wiringPiSetupGpio();
    xio = wiringPiI2CSetup(I2C_ADDR);
    lcd_init();

    setupPins();

    printf("Rasberry Pi Start\n");
    printf("push the button\n");

    while (1) {
        delay(50);
        scanKeys();
    }
    return 0;
>>>>>>> 6c2513a3afce1b7fe07fe8e435bdf28235ffc650
}