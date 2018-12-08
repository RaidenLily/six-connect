#include "gameplay.h"
#include <memory.h>
#include "pvp.h"
#include "QtMultimedia/QSound"

#define chessone ":/Music/Music/chessone.wav"
#define win ":/Music/Music/win.wav"
#define lost ":/Music/Music/lost.wav"

GamePlay::GamePlay()
{
    memset(chess,0,sizeof(chess));
    player=0;
    paint=false;
    able=true;
    full=false;
    chessnum=0;
    first=true;
}

//白为1，黑为2，空为0
void GamePlay::people_putdown(int x,int y)
{
    int temp;
    if(!this->judge(x,y))
        return;
    if(first)
    {
        chess[x][y]=2;
        first=false;
        QSound::play(chessone);
        return;
    }
    QSound::play(chessone);
    temp=player++%4;
    if(temp<=1)
        chess[x][y]=1;
    else
        chess[x][y]=2;
    chessnum++;
    if(chessnum==361)
    {
        full=true;
        able=false;
    }
    return;
}

bool GamePlay::judge(int x,int y)
{
    return chess[x][y]==0? true:false;    //当是空的时候返回对
}

bool GamePlay::win1(int x,int y)  //判断横
{
    int i,cout=0;
    front.x=x;
    front.y=y;
    back.x=x;
    back.y=y;
    for(i=1;i<6;i++)
    {
        if(x-i>=0&&chess[x][y]==chess[x-i][y])
        {
            cout++;
            front.x=x-i;
            front.y=y;
            if(cout==5)
                return true;
        }
        else
            break;
    }
    for(i=1;i<6;i++)
    {
        if(x+i<=18&&chess[x][y]==chess[x+i][y])
        {
            cout++;
            back.x=x+i;
            back.y=y;
            if(cout==5)
                return true;
        }
        else
            break;
    }
    return false;
}

bool GamePlay::win2(int x,int y)   //判断竖
{
    int i,cout=0;
    front.x=x;
    front.y=y;
    back.x=x;
    back.y=y;
    for(i=1;i<6;i++)
    {
        if(y-i>=0&&chess[x][y]==chess[x][y-i])
        {
            cout++;
            front.x=x;
            front.y=y-i;
            if(cout==5)
                return true;
        }
        else
            break;
    }
    for(i=1;i<6;i++)
    {
        if(y+i<=18&&chess[x][y]==chess[x][y+i])
        {
            cout++;
            back.x=x;
            back.y=y+i;
            if(cout==5)
                return true;
        }
        else
            break;
    }
    return false;
}

bool GamePlay::win3(int x,int y)   //判断斜，下同
{
    int i,cout=0;
    front.x=x;
    front.y=y;
    back.x=x;
    back.y=y;
    for(i=1;i<6;i++)
    {
        if(x+i<=18&&y-i>=0&&chess[x][y]==chess[x+i][y-i])
        {
            cout++;
            front.x=x+i;
            front.y=y-i;
            if(cout==5)
                return true;
        }
        else
            break;
    }
    for(i=1;i<6;i++)
    {
        if(x-i>=0&&y+i<=18&&chess[x][y]==chess[x-i][y+i])
        {
            cout++;
            back.x=x-i;
            back.y=y+i;
            if(cout==5)
                return true;
        }
        else
            break;
    }
    return false;
}

bool GamePlay::win4(int x,int y)
{
    int i,cout=0;
    front.x=x;
    front.y=y;
    back.x=x;
    back.y=y;
    for(i=1;i<6;i++)
    {
        if(x-i>=0&&y-i>=0&&chess[x][y]==chess[x-i][y-i])
        {
            cout++;
            front.x=x-i;
            front.y=y-i;
            if(cout==5)
                return true;
        }
        else
            break;
    }
    for(i=1;i<6;i++)
    {
        if(x+i<=18&&y+i<=18&&chess[x][y]==chess[x+i][y+i])
        {
            cout++;
            back.x=x+i;
            back.y=y+i;
            if(cout==5)
                return true;
        }
        else
            break;
    }
    return false;
}

int GamePlay::JudgeWin(int x,int y)
{
    if(win1(x,y)||win2(x,y)||win3(x,y)||win4(x,y))
    {
        paint=true;
        return chess[x][y];
    }
    return false;
}
