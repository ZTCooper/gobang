#include <QPainter>
#include <QPushButton>
#include <QLabel>

#include "dicewindow.h"


#define Dice ":/pics/dice-"

DiceWindow::DiceWindow()
{
    setFixedSize(300, 250);
    okButton = new QPushButton("ok", this);
    okButton->setGeometry(140, 200, 50, 30);
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));

    QFont labelFont;
    labelFont.setPointSize(20);
    labelFont.setBold(true);

    QLabel *blackLabel = new QLabel("黑方", this);
    blackLabel->setAttribute(Qt::WA_DeleteOnClose);
    blackLabel->setFont(labelFont);
    blackLabel->setGeometry(40, 20, 80, 40);

    QLabel *whiteLabel = new QLabel("白方", this);
    whiteLabel->setAttribute(Qt::WA_DeleteOnClose);
    whiteLabel->setFont(labelFont);
    whiteLabel->setGeometry(40, 120, 80, 40);
}

DiceWindow::~DiceWindow()
{
    if(okButton){
        delete okButton;
        okButton = nullptr;
    }
}

void DiceWindow :: setNum(int n1, int n2){
    this->N1 = n1;
    this->N2 = n2;
}

void DiceWindow :: paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap dicePicBlack, dicePicWhite;

    dicePicBlack.load(Dice + QString::number(N1) + ".png");
    dicePicWhite.load(Dice + QString::number(N2) + ".png");
    painter.drawPixmap(120, 10, 70, 70, dicePicBlack);
    painter.drawPixmap(120, 100, 70, 70, dicePicWhite);
}
