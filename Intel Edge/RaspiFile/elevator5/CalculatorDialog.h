#ifndef CALCULATORDIALOG_H
#define CALCULATORDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QStack>
#include <QtMath>
#include <QDebug>
#include <QGridLayout>

class CalculatorDialog : public QDialog {
    Q_OBJECT

public:
    explicit CalculatorDialog(QWidget *parent = nullptr);

private slots:
    void buttonClicked();
    QString calculateExpression(const QString &expression);
    double precedence(QChar op);
    double performOperation(char op, double operand1, double operand2);

private:
    QLineEdit *display;
    QPushButton *buttons[16];
    QStack<char> operators;
    QStack<int> operands;
    QString currentText;
};

#endif // CALCULATORDIALOG_H
