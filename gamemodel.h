#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <vector>
using namespace std;

//游戏类型
enum GameType{
    P2P,    //双人
    BOT     //人机
};

//游戏状态
enum GameStatus{
    PLAYING,    //游戏中
    WIN,        //胜利
    DEAD        //死棋
};

const int BoardSize = 15;   //棋盘尺寸

class GameModel
{
public:
    GameModel(){}
    ~GameModel(){}
public:
    vector<vector<int>> gameMapVec; //存储棋盘和棋子情况，空白为0，白1，黑-1
    vector<vector<int>> scoreMapVec;    //存储各点位评分
    bool playerFlag; //标志下棋方（己方为1，对方为0）
    GameType gameType; //游戏类型
    GameStatus gameStatus; //游戏状态

    void startGame(GameType type); //游戏开始
    void calculateScore(); //计算评分
    void actionByPerson(int rou, int col); //人下棋
    void actionByBot(int &clickRow, int &clickCol); //机器下棋
    void updateGameMap(int row, int col); //落子后更新棋盘
    bool isWin(int row, int col); //判断胜利
    bool isDead();  //判断死棋
};

#endif // GAMEMODEL_H
