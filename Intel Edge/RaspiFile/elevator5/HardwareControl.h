#ifndef HARDWARECONTROL_H
#define HARDWARECONTROL_H

#include "commonval.h"
#include <QObject>
class DisplayThread;

// Keypad
#define C4 6
#define C3 13
#define C2 19
#define C1 26
#define R4 12
#define R3 16
#define R2 20
#define R1 21

//int diginum = {12, 9, 8, 6};
extern int diginum[5];
//int segnum = {11, 7, 4, 2, 1, 10, 5, 3};
extern int segnum[9];
extern int numlist[17][9];
extern int digicnt;
extern int segcnt;
extern char inputBuffer[11];
extern int bufferIndex;
extern int displayValue;
extern int currentNumber;
extern int lastButtonState[4][4];
extern char buttonValues[4][4];

void digiInit();
void setupPins();

namespace Ui {
    class elevatorPanel;
}

class HardwareControl : public QObject {
    Q_OBJECT

public:
    HardwareControl(QObject *parent = nullptr);

    void displayNumber();
    void scanKeys();
    void startElevator();
    void stopElevator();

public slots:

private:
    DisplayThread *displayThread;
};

#endif // HARDWARECONTROLLER_H
