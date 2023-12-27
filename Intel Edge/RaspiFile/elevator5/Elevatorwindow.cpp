#include "Elevatorwindow.h"
#include "HardwareControl.h"

ElevatorWindow::ElevatorWindow(QWidget *parent) : QDialog(parent) {
    int dialogWidth = 200;
    int dialogHeight = 100;
    int buttonWidth = 100;
    int buttonHeight = 30;

    int x = (dialogWidth - buttonWidth) / 2; // 대화상자 너비의 중간
    int y = (dialogHeight - buttonHeight) / 2; // 대화상자 높이의 중간

    ElevatorPanel *panel = new ElevatorPanel(this);

    QPushButton *startButton = new QPushButton("Start", this);
    startButton->setGeometry(x, y, buttonWidth, buttonHeight);
    connect(startButton, &QPushButton::clicked, this, &ElevatorWindow::onStartButtonClicked);
}
void ElevatorWindow::on_elevatorButton_clicked() {
    HardwareControl hardware;
    hardware.startElevator();
}
void ElevatorWindow::onStartButtonClicked() {
    HardwareControl hardwareControl;
    hardwareControl.scanKeys();
    hardwareControl.displayNumber();
}
