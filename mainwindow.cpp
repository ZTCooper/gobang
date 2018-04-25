#include <QPainter>
#include<QMenuBar>
#include<QMenu>
#include "mainwindow.h"

const int BoardMargin = 30; // 棋盘边缘空隙
const int BlockSize = 40; // 格子的大小
const int Padding = 20; // 棋盘boarder到坐标距离

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置棋盘大小 背景色
    setFixedSize(BoardMargin * 2 + BlockSize * BoardSize, BoardMargin * 2 + BlockSize * BoardSize);
    setStyleSheet("background-color:rgb(217,171,130);");
    //开启鼠标hover功能
    setMouseTracking(true);

    //添加菜单
    QMenu *gameMenu = menuBar()->addMenu(tr("Game"));   //menuBar默认存在

    QAction *actionPVP = new QAction("Person VS Person", this);
    connect(actionPVP, SIGNAL(triggered()), this, SLOT(initPVPGame()));
    gameMenu->addAction(actionPVP);

    QAction *actionPVB = new QAction("Person VS Computer", this);
    connect(actionPVB, SIGNAL(triggered()), this, SLOT(initPVBGame()));
    gameMenu->addAction(actionPVB);

    //开始游戏
    initGame();
}

MainWindow::~MainWindow()
{
    if(game){
        delete game;
        game = nullptr;
    }
}

void MainWindow::initGame(){
    game = new GameModel;
    initPVPGame();
}

void MainWindow::initPVPGame(){
    game_type = PVP;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();
}

void MainWindow::initPVBGame(){
    game_type = PVB;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){

}

void MainWindow::chessOneByPerson(){

}

void MainWindow::chessOneByBot(){

}

//绘图
void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing, true);    //抗锯齿

    for(int i = 0; i <= BoardSize; i++){
        painter.drawLine(BoardMargin + BlockSize * i, BoardMargin, BoardMargin + BlockSize * i, size().height() - BoardMargin);
        painter.drawLine(BoardMargin, BoardMargin + BlockSize * i, size().width() - BoardMargin, BoardMargin + BlockSize * i);

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
    }
    //设置字体
    QFont font;
    font.setPointSize(8);
    font.setBold(true);
    painter.setFont(font);
    //绘制坐标
    vector<QString> xLabel {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O"};
    for(int i = 0; i <= BoardSize; i++){
        painter.drawText(QPoint(BoardMargin + BlockSize * i - font.pointSize()/2, BoardMargin + BlockSize * BoardSize + Padding), QString(xLabel[i]));
        painter.drawText(QPoint(Padding - font.pointSize(), BoardMargin + BlockSize * (BoardSize - i) + font.pointSize()/2), QString(QString::number(i + 1)));
    }

}

