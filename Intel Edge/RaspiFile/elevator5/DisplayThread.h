#ifndef DISPLAYTHREAD_H
#define DISPLAYTHREAD_H

#include <QThread>
#include <QMutex>
#include <QDebug>
#include <wiringPi.h>

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
extern int diginum[4];
//int segnum = {11, 7, 4, 2, 1, 10, 5, 3};
extern int segnum[8];
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

class DisplayThread : public QThread {
    Q_OBJECT

public:
    DisplayThread(QObject *parent = nullptr);
    void run() override;

signals:
    void updateDisplay(int number);

public slots:
    void setNumber(int number);

private:
    int currentNumber;
        QMutex mutex;
};

#endif // DISPLAYTHREAD_H
