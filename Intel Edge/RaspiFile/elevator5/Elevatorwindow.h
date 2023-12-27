#ifndef ELEVATORWINDOW_H
#define ELEVATORWINDOW_H

#include "commonval.h"
#include "HardwareControl.h"
#include "elevatorPanel.h"

class ElevatorWindow : public QDialog {
    Q_OBJECT

public:
    ElevatorWindow(QWidget *parent = nullptr);
    QPushButton *newButton;

private slots:
    void on_elevatorButton_clicked();
    void onStartButtonClicked();

private:
    HardwareControl hardware;
};

#endif // ELEVATORWINDOW_H
