#include ""adc_v1.h"

int main()
{
	wiringPiSetupGpio();
	xio = wiringPiI2CSetup(I2C_ADDR);

	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
	softPwmCreate(pinLed, 0, 200);
	mcp3004Setup(BASE, SPI_CHAN);

	char line1[100];

	lcd_init();
	setupPins();
	lcdClear();
	lcdLoc(LINE1);
	sprintf(line1, "Start");
	typeln(line1);

	while (1) {
		delay(100);
		scanKeys();
	}

	return 0;
}