#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QTimer>
#include <QDebug>
#include <QtConcurrent>
#include "DisplayThread.h"
#include "CalculatorDialog.h"

void setupPins();

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void scanKeys();
    void increaseNumber(int targetNumber);

private slots:
    void on_pushButton_clicked();
    void on_label_linkActivated(const QString &link);
    void on_buttonCalculator_clicked();

private:
    Ui::MainWindow *ui;
    DisplayThread *displayThread;
    CalculatorDialog *calculatorDialog;
};
#endif // MAINWINDOW_H
