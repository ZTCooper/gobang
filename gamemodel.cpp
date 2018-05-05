#include "gamemodel.h"


//游戏开始，，初始化棋盘格和评分表
void GameModel::startGame(GameType type){
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
    if(gameType == PVB){
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

void GameModel::updateGameMap(int row, int col){
    if(playerFlag)
        gameMapVec[row][col] = 1;
    else
        gameMapVec[row][col] = -1;

    // 交换棋权
    playerFlag = !playerFlag;
}

void GameModel::actionByPerson(int row, int col){
    updateGameMap(row, col);
}

//判断输赢
bool GameModel::isWin(int row, int col){
    //水平方向
    for(int i = 0; i < 5; i++){
        if(col - i > 0 &&
           col - i + 4 < BoardSize &&
           gameMapVec[row][col - i] == gameMapVec[row][col - i + 1] &&
           gameMapVec[row][col - i] == gameMapVec[row][col - i + 2] &&
           gameMapVec[row][col - i] == gameMapVec[row][col - i + 3] &&
           gameMapVec[row][col - i] == gameMapVec[row][col - i + 4])
            return true;
    }

    //竖直方向
    for(int i = 0; i < 5; i++){
        if(row - i > 0 &&
           row - i + 4 < BoardSize &&
           gameMapVec[row - i][col] == gameMapVec[row - i + 1][col] &&
           gameMapVec[row - i][col] == gameMapVec[row - i + 2][col] &&
           gameMapVec[row - i][col] == gameMapVec[row - i + 3][col] &&
           gameMapVec[row - i][col] == gameMapVec[row - i + 4][col])
            return true;
    }

    //主对角线
    for(int i = 0; i < 5; i++){
        if(row - i > 0 &&
           row - i + 4 < BoardSize &&
           col - i > 0 &&
           col - i + 4 < BoardSize &&
           gameMapVec[row - i][col - i] == gameMapVec[row - i + 1][col - i + 1] &&
           gameMapVec[row - i][col - i] == gameMapVec[row - i + 2][col - i + 2] &&
           gameMapVec[row - i][col - i] == gameMapVec[row - i + 3][col - i + 3] &&
           gameMapVec[row - i][col - i] == gameMapVec[row - i + 4][col - i + 4])
            return true;
    }

    //副对角线
    for(int i = 0; i < 5; i++){
        if(row - i < BoardSize &&
           row - i + 4 > 0 &&
           col - i > 0 &&
           col - i + 4 < BoardSize &&
           gameMapVec[row - i][col + i] == gameMapVec[row - i + 1][col + i - 1] &&
           gameMapVec[row - i][col + i] == gameMapVec[row - i + 2][col + i - 2] &&
           gameMapVec[row - i][col + i] == gameMapVec[row - i + 3][col + i - 3] &&
           gameMapVec[row - i][col + i] == gameMapVec[row - i + 4][col + i - 4])
            return true;
    }

    return false;
}

//判断死棋
bool GameModel::isDead(){
    for(int i = 0; i < BoardSize; i++){
        for(int j = 0; j < BoardSize; j++)
            if(gameMapVec[i][j] == 0)
                return false;
    }
    return true;
}

void GameModel::calculateScore(){

}

void GameModel::actionByBot(int &clickRow, int &clickCol){

}


