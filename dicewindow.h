#ifndef DICEWINDOW_H
#define DICEWINDOW_H
#include <QDialog>

class DiceWindow : public QDialog
{
    Q_OBJECT

public:
    DiceWindow();
    ~DiceWindow();
    void setNum(int n1, int n2);

private:
    QPushButton *okButton;
    int N1, N2;


protected:
    void paintEvent(QPaintEvent *event);
};

#endif // DICEWINDOW_H
