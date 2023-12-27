#ifndef ELEVATORPANEL_H
#define ELEVATORPANEL_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class ElevatorPanel : public QDialog {
    Q_OBJECT

public:
    explicit ElevatorPanel(QWidget *parent = nullptr);

private:
    QPushButton *buttonExample;
    QLabel *labelExample;
};

#endif // ELEVATORPANEL_H
