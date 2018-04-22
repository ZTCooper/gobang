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

}

void MainWindow::initPVPGame(){

}

void MainWindow::initPVBGame(){

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
