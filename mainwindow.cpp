#include <QPainter>
#include <QMenuBar>
#include <QMenu>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QPalette>
#include <QSound>
#include "dicewindow.h"
#include "mainwindow.h"

#define CHESS_ONE_SOUND ":/sounds/chessone.wav"
#define WIN_SOUND ":/sounds/win.wav"
#define OCCUPIED_SOUND ":/sounds/occupied.wav"

const int BoardMargin = 30; // 棋盘边缘空隙
const int BlockSize = 40; // 格子的大小
const int Padding = 10; // 棋盘border到坐标距离
const int PosEps = BlockSize/2; // 鼠标点击落子的模糊距离
const int MarkSize = 6; // 落子时标记边长
const int Radius = 15; // 棋子半径
const int countdown = 30;   //倒计时
int t = countdown;
bool timerFlag = 0;   //是否已有Timer
const int Delay = 700;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置棋盘大小 背景色
    setFixedSize(BoardMargin * 2 + BlockSize * BoardSize + 200, BoardMargin * 2 + BlockSize * BoardSize);
    setStyleSheet("background-color:rgb(217,171,130);");
    //开启鼠标hover功能
    setMouseTracking(true);

    QFont labelFont;
    labelFont.setPointSize(20);
    labelFont.setBold(true);

    QFont buttonFont;
    buttonFont.setPointSize(12);
    buttonFont.setBold(true);
    // 执棋方
    QLabel *chessLabel = new QLabel("执棋方：", this);
    chessLabel->setAttribute(Qt::WA_DeleteOnClose);
    chessLabel->setFont(labelFont);
    chessLabel->setGeometry(size().width() - 175, 100, 200, 50);

    startButton = new QPushButton("双人对战", this);
    startButton->setGeometry(size().width() - 150, size().height() - 200, 100, 45);
    startButton->setFont(buttonFont);
    connect(startButton, SIGNAL(clicked(bool)), this, SLOT(showRandom()));

    restartButton = new QPushButton("人机对战", this);
    restartButton->setGeometry(size().width() - 150, size().height() - 150, 100, 45);
    restartButton->setFont(buttonFont);
    connect(restartButton, SIGNAL(clicked(bool)), this, SLOT(initPVBGame()));

    exitButton = new QPushButton("退出游戏", this);
    exitButton->setGeometry(size().width() - 150, size().height() - 100, 100, 45);
    exitButton->setFont(buttonFont);
    connect(exitButton, SIGNAL(clicked(bool)), this, SLOT(exitGame()));

    //开始游戏
    initPVPGame();
}

MainWindow::~MainWindow()
{
    if(game){
        delete game;
        game = nullptr;
    }
    if(startButton){
        delete startButton;
        startButton = nullptr;
    }
    if(restartButton){
        delete restartButton;
        restartButton = nullptr;
    }
    if(exitButton){
        delete exitButton;
        exitButton = nullptr;
    }

}


void MainWindow::showRandom(){
    DiceWindow *diceWindow = new DiceWindow();
    diceWindow->setWindowTitle("Who's first");
    diceWindow->setAttribute(Qt::WA_DeleteOnClose);

    int N1, N2;
    N1 = 1 + rand() % 6;
    N2 = 1 + rand() % 6;
    while(N2 == N1){
        N2 = 1 + rand() % 6;
    }

    diceWindow->setNum(N1, N2);
    diceWindow->setModal(true);

    int ret = diceWindow->exec();
    if(ret == QDialog::Accepted){
        game = new GameModel;
        game_type = PVP;
        game->gameStatus = PLAYING;
        game->startGame(game_type);
        if(N1 < N2){
            game->playerFlag = true;    // 白子大，白子先走
        }
        else{
            game->playerFlag = false;   // 黑子大，黑子先走
        }
    }
}


void MainWindow::initPVPGame(){
    game = new GameModel;
    game_type = PVP;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    t = -1;      // 第一次落子不需要计时
    if (!timerFlag)     // 避免重复创建timer
        createTimer();
    update();
}

void MainWindow::initPVBGame(){
    game = new GameModel;
    game_type = PVB;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();
}

void MainWindow::createTimer(){
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTimeLimit()));
    timer->start(1000);
    timerFlag = 1;      // 已创建timer
}

void MainWindow::showTimeLimit(){
    QFont font;
    font.setPointSize(30);
    font.setBold(true);
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::red);

    QLabel *timeLabel = new QLabel(this);
    timeLabel->setAttribute(Qt::WA_DeleteOnClose);
    timeLabel->setGeometry(size().width() - 120, size().height() - 300, 100, 50);
    timeLabel->setFont(font);
    timeLabel->setPalette(pe);
    if(t > 0){
        timeLabel->setText(QString::number(t));
        t--;
    }
    else if(t == 0){
        timeLabel->setText(QString::number(t));
        game->playerFlag = !game->playerFlag;
        t = countdown;
    }
    timeLabel->show();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    // 鼠标hover确定落子点
    int x = event->x();
    int y = event->y();
    //qDebug("%d %d", x, y);
    // 判断位置在棋盘格内
    if(x >= BoardMargin &&
            x < size().width() - BoardMargin &&
            y > BoardMargin  &&
            y < size().height() - BoardMargin)
    {
        // 行 列
        int col = (x - BoardMargin) / BlockSize;
        int row = (y - BoardMargin) / BlockSize;
        //qDebug("%d %d", row, col);
        // 找点击点的左上角点坐标
        int leftTopPosX = BoardMargin + col * BlockSize;
        int leftTopPosY = BoardMargin + row * BlockSize;
        // 左下
        int leftDownPosX = leftTopPosX;
        int leftDownPosY = leftTopPosY + BlockSize;
        // 右上
        int rightTopPosX = leftTopPosX + BlockSize;
        int rightTopPosY = leftTopPosY;
        // 右下
        int rightDownPosX = rightTopPosX;
        int rightDownPosY = rightTopPosY + BlockSize;

        // 初始化，计算点击点与四周点的距离
        clickRow = -1;
        clickCol = -1;
        int dist = 0;

        dist = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if(dist < PosEps){
            clickRow = row;
            clickCol = col;
        }//左上
        dist = sqrt((x - leftDownPosX) * (x - leftDownPosX) + (y - leftDownPosY) * (y - leftDownPosY));
        if(dist < PosEps){
            clickRow = row + 1;
            clickCol = col;
        }// 左下
        dist = sqrt((x - rightTopPosX) * (x - rightTopPosX) + (y - rightTopPosY) * (y - rightTopPosY));
        if(dist < PosEps){
            clickRow = row;
            clickCol = col + 1;
        }// 右上
        dist = sqrt((x - rightDownPosX) * (x - rightDownPosX) + (y - rightDownPosY) * (y - rightDownPosY));
        if(dist < PosEps){
            clickRow = row + 1;
            clickCol = col + 1;
        }// 右下
        //qDebug("%d %d", clickRow, clickCol);
    }

    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(!(game_type == PVB && !game->playerFlag)){
        t = countdown;      // 每次落子后开始倒计时
        chessOneByPerson();
        if(game->gameType == PVB && !game->playerFlag){
            QTimer::singleShot(Delay, this, SLOT(chessOneByBot()));
        }
    }
}

void MainWindow::chessOneByPerson(){
    if(clickRow != -1 && clickCol != -1){
        if(game->gameMapVec[clickRow][clickCol] == 0){
            game->actionByPerson(clickRow, clickCol);
            QSound::play(CHESS_ONE_SOUND);
            t = countdown;
            update();
        }
        else
            QSound::play(OCCUPIED_SOUND);   // 该位置已有棋子，发出提示音
    }
}

void MainWindow::chessOneByBot(){
    game->actionByBot(clickRow, clickCol);
    QSound::play(CHESS_ONE_SOUND);
    update();
}

//绘图
void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    //绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing, true);    //抗锯齿

    for(int i = 0; i <= BoardSize; i++){
        painter.drawLine(QPoint(BoardMargin, BoardMargin + BlockSize * i), QPoint(BoardMargin + BoardSize * BlockSize, BoardMargin + BlockSize * i));
        painter.drawLine(QPoint(BoardMargin + BlockSize * i, BoardMargin), QPoint(BoardMargin + BlockSize * i, BoardMargin + BoardSize * BlockSize));
    }

    //设置字体
    QFont font;
    font.setPointSize(8);
    font.setBold(true);
    painter.setFont(font);

    //绘制坐标
    vector<QString> xLabel {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O"};
    for(int i = 0; i <= BoardSize; i++){
        painter.drawText(QPoint(BoardMargin + BlockSize * i - font.pointSize()/2, size().height() - Padding), QString(xLabel[i]));
        painter.drawText(QPoint(Padding, BoardMargin + BlockSize * (BoardSize - i) + font.pointSize()/2), QString(QString::number(i + 1)));
    }

    // 绘制落子标记方框
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    //qDebug("%d %d", clickRow, clickCol);
    if(clickRow >= 0 && clickRow <= BoardSize &&
       clickCol >= 0 && clickCol <= BoardSize &&
       game->gameMapVec[clickRow][clickCol] == 0)   //判断在棋盘格范围内且该点无棋子
    {
        if(game->playerFlag)    // 己方
            brush.setColor(Qt::white);
        else
            brush.setColor(Qt::black);
        painter.setBrush(brush);
        painter.drawRect(BoardMargin + BlockSize * clickCol - MarkSize/2, BoardMargin + BlockSize * clickRow - MarkSize/2, MarkSize, MarkSize);
    }

    // 绘制棋子
    for(int i = 0; i < BoardSize; i++){
        for(int j = 0; j < BoardSize; j++){
            if(game->gameMapVec[i][j] == 1){    // 己方
                brush.setColor(Qt::white);      // 白色
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(BoardMargin + j * BlockSize, BoardMargin + i * BlockSize), Radius, Radius);
            }
            if(game->gameMapVec[i][j] == -1){    // 对方
                brush.setColor(Qt::black);      // 黑色
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(BoardMargin + j * BlockSize, BoardMargin + i * BlockSize), Radius, Radius);
            }
        }
    }

    // 绘制执棋方棋子
    if(game->playerFlag)
        brush.setColor(Qt::white);
    else
        brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawEllipse(QPoint(size().width() - 100, 200), 2 * Radius, 2 * Radius);

    // 判断输赢
    if(clickRow > 0 && clickRow < BoardSize &&
       clickCol > 0 && clickRow < BoardSize &&(
       game->gameMapVec[clickRow][clickCol] == 1 ||
       game->gameMapVec[clickRow][clickCol] == -1))
    {
        if(game->isWin(clickRow, clickCol) && game->gameStatus == PLAYING){
            qDebug("win");
            t = -1;     //计时器停止
            game->gameStatus = WIN;
            QSound::play(WIN_SOUND);

            QString winner;

            if(game->gameMapVec[clickRow][clickCol] == 1)
                winner = "White wins!";
            else if(game->gameMapVec[clickRow][clickCol] == -1)
                winner = "Black wins!";

            int answer = QMessageBox::warning(NULL, "Congratulations", winner + "\nWanna play again?", QMessageBox::Yes, QMessageBox::No);

            // 点击Yes重新开始游戏
            if(answer == QMessageBox::Yes){
                game->startGame(game_type);
                game->gameStatus = PLAYING;
            }
            else if(answer == QMessageBox::No){
                QApplication::quit();
            }
        }
    }
}

void MainWindow::exitGame(){
    t = -1;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
                NULL, "Warning", QString::fromUtf8("确定退出吗？"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(reply == QMessageBox::Yes) this->close();

}

