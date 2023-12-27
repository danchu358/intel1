#include "elevatorPanel.h"

ElevatorPanel::ElevatorPanel(QWidget *parent) : QDialog(parent) {
    buttonExample = new QPushButton("버튼 예시", this);
    labelExample = new QLabel("레이블 예시", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(labelExample);
    layout->addWidget(buttonExample);

    setLayout(layout);
}
