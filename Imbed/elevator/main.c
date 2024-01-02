#include "fnd_v5.h"

int main()
{
     wiringPiSetupGpio();
     xio = wiringPiI2CSetup(I2C_ADDR);

     printf("FND 7 Segment Start\n");
     digiOff();
     segOff();

     setupPins();

     while (1) {
         digitalWrite(diginum[0], HIGH);
         numlist[0][0];
         seg_0();
         delay(1);
         digiOff();
         segOff();

         digitalWrite(diginum[1], HIGH);
         seg_1();
         delay(1);
         digiOff();
         segOff();
 
         digitalWrite(diginum[2], HIGH);
         seg_0();
         delay(1);
         digiOff();
         segOff();
 
         digitalWrite(diginum[3], HIGH);
         seg_1();
         delay(1);
         digiOff();
         segOff();
      }
     return 0;
}

