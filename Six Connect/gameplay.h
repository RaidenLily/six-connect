#ifndef GAMEPLAY_H
#define GAMEPLAY_H

struct DrawLine   //赢了之后划线的结构
{
    int x;
    int y;
};

class GamePlay   //游戏主逻辑
{
public:
    GamePlay();
    void people_putdown(int ,int);
    bool judge(int,int);   //判断当前是否是空的，是空返回true
    int chess[19][19];    //二维数组表棋盘
    int JudgeWin(int,int);
    int chessnum;//记录下的棋子数
    bool paint;    //是否连线
    bool able;     //游戏是否可操作
    bool full;     //棋盘是否满了
    bool first;
    int player;
    DrawLine front;    //赢了的时候标记划线的头部
    DrawLine back;

private:
    bool win1(int,int);
    bool win2(int,int);
    bool win3(int,int);
    bool win4(int,int);
};

#endif // GAMEPLAY_H
