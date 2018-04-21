#include "gamemodel.h"

GameModel::GameModel()
{

}

void GameModel :: startGame(GameType type){
    gameType = type;

    //清空棋盘
    gameMapVec.clear();
    //所有点初始化为0
    for(int i = 0; i < BoardSize; i++){
        vector<int> lineBoard;
        for(int j = 0; j < BoardSize; j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);
    }

    //人机模式需清空并初始化评分vec
    if(gameType == BOT){
        scoreMapVec.clear();
        for(int i = 0; i < BoardSize; i++){
            vector<int> lineBoard;
            for(int j = 0; j < BoardSize; j++)
                lineBoard.push_back(0);
            scoreMapVec.push_back(lineBoard);
        }
    }

    //己方为1，对方为0
    playerFlag = true;
}
