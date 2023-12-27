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

        // currentText 변수를 사용하여 사용자 입력 처리
        if (buttonText >= '0' && buttonText <= '9') {
            currentText += buttonText; // 숫자 버튼을 누를 때 currentText에 추가
            display->setText(currentText);
        } else if (buttonText == '+' || buttonText == '-' || buttonText == '*' || buttonText == '/') {
            currentText += " " + buttonText + " "; // 연산자 버튼을 누를 때 currentText에 추가
            display->setText(currentText);
        } else if (buttonText == "=") {
            QString resultText = calculateExpression(currentText);
            display->setText(resultText);
            currentText = resultText; // 결과를 다시 currentText로 설정
        } else if (buttonText == "C") {
            currentText.clear(); // "C" 버튼을 누를 때 currentText 초기화
            display->clear();
        }
    }
}
QString CalculatorDialog::calculateExpression(const QString &expression) {
    QStack<int> operandStack;
    QStack<QChar> operatorStack;

    for (int i = 0; i < expression.length(); i++) {
        QChar ch = expression[i];

        if (ch.isDigit()) {
            QString operandStr;
            operandStr += ch;

            while (i + 1 < expression.length() && expression[i + 1].isDigit()) {
                operandStr += expression[i + 1];
                i++;
            }

            int operand = operandStr.toInt();
            operandStack.push(operand);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!operatorStack.isEmpty() &&
                   precedence(ch) <= precedence(operatorStack.top())) {
                char op = operatorStack.pop().toLatin1();
                int operand1 = operandStack.pop();
                int operand2 = operandStack.pop();
                int result = performOperation(op, operand1, operand2);
                operandStack.push(result);
            }
            operatorStack.push(ch);
        }
    }

    while (!operatorStack.isEmpty()) {
        char op = operatorStack.pop().toLatin1();
        int operand1 = operandStack.pop();
        int operand2 = operandStack.pop();
        int result = performOperation(op, operand1, operand2);
        operandStack.push(result);
    }

    if (!operandStack.isEmpty()) {
        int finalResult = operandStack.top();
        return QString::number(finalResult);
    }
    else {
        return "Error";
    }
}
int CalculatorDialog::precedence(QChar op) {
    if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    }
    return 0;
}
int CalculatorDialog::performOperation(char op, int operand1, int operand2) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) {
                return operand1 / operand2;
            } else {
                return 0; // 나누기 0 에러 처리
            }
        default:
            return 0; // 알 수 없는 연산자 에러 처리
    }
}
