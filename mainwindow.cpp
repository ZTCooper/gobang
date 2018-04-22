#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::paintEvent(QPaintEvent *event){

}
