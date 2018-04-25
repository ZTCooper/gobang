#include <QPainter>
#include "mainwindow.h"

const int BoardMargin = 30; // 棋盘边缘空隙
const int BlockSize = 40; // 格子的大小
const int Padding = 20; // 棋盘boarder到坐标距离

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置棋盘大小
    setFixedSize(BoardMargin * 2 + BlockSize * BoardSize, BoardMargin * 2 + BlockSize * BoardSize);
    setStyleSheet("background-color:rgb(217,171,130);");
}

MainWindow::~MainWindow()
{

}

void MainWindow::initGame(){
    game = new GameModel;
    initPVPGame();
}

void MainWindow::initPVPGame(){
    game_type = P2P;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();
}

void MainWindow::initPVBGame(){
    game_type = BOT;
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
    for(int i = 0; i <= BoardSize; i++){
        painter.drawText(QPoint(BoardMargin + BlockSize * i - font.pointSize()/2, Padding), QString(QString::number(i + 1)));
        painter.drawText(QPoint(Padding - font.pointSize(), BoardMargin + BlockSize * i + font.pointSize()/2), QString(QString::number(i + 1)));
    }

}

