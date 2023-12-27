#include "CalculatorDialog.h"

CalculatorDialog::CalculatorDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Calculator");
    QVBoxLayout *layout = new QVBoxLayout;

    display = new QLineEdit(this);
    display->setReadOnly(true);
    layout->addWidget(display);

    QGridLayout *gridLayout = new QGridLayout;
    const char *buttonLabels[16] = {
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "C", "0", "=", "+"
    };

    for (int i = 0; i < 16; i++) {
            buttons[i] = new QPushButton(buttonLabels[i]);
            gridLayout->addWidget(buttons[i], i / 4, i % 4);
            connect(buttons[i], &QPushButton::clicked, this, &CalculatorDialog::buttonClicked);
    }

    layout->addLayout(gridLayout);
    setLayout(layout);

}
void CalculatorDialog::buttonClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (clickedButton) {
        QString buttonText = clickedButton->text();

        if (buttonText >= '0' && buttonText <= '9') {
            currentText += buttonText;
        }
        else if (buttonText == '+' || buttonText == '-' || buttonText == 'x' || buttonText == '/') {
            if (buttonText == 'x') {
                currentText += " * ";
                display->setText(currentText);
            }
            else {
                currentText += " " + buttonText + " ";
                display->setText(currentText);
            }
        }
        else if (buttonText == "=") {
            QString resultText = calculateExpression(currentText);
            currentText = resultText;
            display->setText(resultText);
        }
        else if (buttonText == "C") {
            currentText.clear();
            display->clear();
        }
        display->setText(currentText);
    }
}
QString CalculatorDialog::calculateExpression(const QString &expression) {
    QStack<double> operandStack;
    QStack<QChar> operatorStack;

    QStringList tokens = expression.split(" ", Qt::SkipEmptyParts);

    for (const QString &token : tokens) {
        bool ok;
        double value = token.toDouble(&ok);
        if (ok) {
            operandStack.push(value);
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            while (!operatorStack.isEmpty() && precedence(token[0]) <= precedence(operatorStack.top())) {
                double operand2 = operandStack.pop(); // 먼저 꺼낸 피연산자가 두 번째 피연산자가 됩니다.
                double operand1 = operandStack.pop();
                char op = operatorStack.pop().toLatin1();
                operandStack.push(performOperation(op, operand1, operand2));
                if (op == '+') {
                    operandStack.push(operand1 + operand2);
                }
                else if (op == '-') {
                    operandStack.push(operand1 - operand2);
                }
                else if (op == '*') {
                    operandStack.push(operand1 * operand2);
                }
                else if (op == '/') {
                    if (operand2 != 0) {
                        operandStack.push(operand1 / operand2);
                    }
                    else {
                        return "Error";
                    }
                }
            }
            operatorStack.push(token[0]);
        }
    }

    while (!operatorStack.isEmpty()) {
       double operand2 = operandStack.pop();
       double operand1 = operandStack.pop();
       char op = operatorStack.pop().toLatin1();
       operandStack.push(performOperation(op, operand1, operand2));
   }

    return !operandStack.isEmpty() ? QString::number(operandStack.top()) : "Error";
}
double CalculatorDialog::precedence(QChar op) {
    if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    }
    return 0;
}
double CalculatorDialog::performOperation(char op, double operand1, double operand2) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) {
                return static_cast<double>(operand1) / operand2;
            }
            else {
                return std::numeric_limits<double>::quiet_NaN();
            }
        default:
            return std::numeric_limits<double>::quiet_NaN();
    }
}
