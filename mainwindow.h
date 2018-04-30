#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gamemodel.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    //绘制
    void paintEvent(QPaintEvent *event);
    //监听鼠标移动
    void mouseMoveEvent(QMouseEvent *event);
    //鼠标松开（落子）
    void mouseReleaseEvent(QMouseEvent *event);

private:
    GameModel *game;    //游戏指针
    GameType game_type;     //存储游戏类型
    int clickRow, clickCol;   //存储点击位置（行，列）
    void initGame();    //初始化
    void checkGame(int y, int x);

private slots:  //信号槽
    void chessOneByPerson();    //人下棋
    void chessOneByBot();   //机器下棋
    void initPVPGame();     //初始化人对人
    void initPVBGame();     //初始化人机
    //void showTimeLimit();   //显示倒计时
};

#endif // MAINWINDOW_H
