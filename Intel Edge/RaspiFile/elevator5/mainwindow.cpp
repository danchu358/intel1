#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupPins();

    // DisplayThread 인스턴스 생성 및 시작
    displayThread = new DisplayThread(this);
    displayThread->start();

    // CalculatorDialog 객체 생성
    calculatorDialog = new CalculatorDialog(this);
    calculatorDialog->hide();

    // scanKeys 타이머 설정
    QTimer *keypadTimer = new QTimer(this);
    connect(keypadTimer, &QTimer::timeout, this, &MainWindow::scanKeys);
    keypadTimer->start(100);

    // 새로운 파란색 버튼 생성 및 설정
    blueButton = new QPushButton("Blue Button", this);
    blueButton->setStyleSheet("background-color: blue; color: white;");
    blueButton->setGeometry(QRect(100, 100, 100, 50)); // 위치와 크기 설정

    connect(blueButton, &QPushButton::clicked, this, &MainWindow::onBlueButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;

    displayThread->terminate();
    displayThread->wait();
}
void MainWindow::on_pushButton_clicked()
{
    ui->label->setText("FND 7 Segment Start\n");
    digiInit();
}
void MainWindow::scanKeys() {
    int currentButtonState;
    char input;

    for (int row = 0; row < 4; ++row) {
        digitalWrite(R1, row == 0 ? LOW : HIGH);
        digitalWrite(R2, row == 1 ? LOW : HIGH);
        digitalWrite(R3, row == 2 ? LOW : HIGH);
        digitalWrite(R4, row == 3 ? LOW : HIGH);

        for (int col = 0; col < 4; ++col) {
            switch (col) {
            case 0: currentButtonState = digitalRead(C1); break;
            case 1: currentButtonState = digitalRead(C2); break;
            case 2: currentButtonState = digitalRead(C3); break;
            case 3: currentButtonState = digitalRead(C4); break;
            }

            // 상태 변화가 감지될 경우에만 처리
            if (currentButtonState == LOW && lastButtonState[row][col] == HIGH) {
                delay(100);
                input = buttonValues[row][col];
                qDebug() << "Button pressed:" << input;
                ui->label->setText(QString("현재숫자: %1").arg(input));

                if (input >= '0' && input <= '9' && bufferIndex < 10) {
                    inputBuffer[bufferIndex++] = input;
                }
                else if (input == '#') {
                    inputBuffer[bufferIndex] = '\0';
                    int targetNumber = atoi(inputBuffer);

                    increaseNumber(targetNumber);

                    memset(inputBuffer, 0, sizeof(inputBuffer));
                    bufferIndex = 0;
                }
            }
            lastButtonState[row][col] = currentButtonState;
        }
    }
}
void setupPins() {
    // 행을 출력으로 설정
    pinMode(R1, OUTPUT);
    pinMode(R2, OUTPUT);
    pinMode(R3, OUTPUT);
    pinMode(R4, OUTPUT);

    // 열을 입력으로 설정
    pinMode(C1, INPUT);
    pinMode(C2, INPUT);
    pinMode(C3, INPUT);
    pinMode(C4, INPUT);

    // 내부 풀업 저항 활성화
    pullUpDnControl(C1, PUD_UP);
    pullUpDnControl(C2, PUD_UP);
    pullUpDnControl(C3, PUD_UP);
    pullUpDnControl(C4, PUD_UP);
}
void MainWindow::on_label_linkActivated(const QString &link) {

}
void MainWindow::increaseNumber(int targetNumber) {
    QtConcurrent::run([=] {
        if (currentNumber < targetNumber) {
            for (int i = currentNumber; i <= targetNumber; i++) {
                displayThread->setNumber(i);
                QThread::msleep(1000);
            }
        }
        else if (currentNumber > targetNumber) {
            for (int i = currentNumber; i >= targetNumber; i--) {
                displayThread->setNumber(i);
                QThread::msleep(1000);
            }
        }
        currentNumber = targetNumber;
    });
}
void MainWindow::on_buttonCalculator_clicked()
{
    calculatorDialog->show();
}
void MainWindow::onBlueButtonClicked() {
    qDebug() << "Blue button clicked!";
}
