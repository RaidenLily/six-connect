#ifndef PVE_H
#define PVE_H

#pragma execution_character_set("utf-8")

#include <other.h>
#include "gameplay.h"
#include <QMouseEvent>
#include <vector>
#include <stdlib.h>
#include <time.h>

struct chessdata
{
    int x;
    int y;
    bool computer;
};

namespace Ui {
class PVE;
}

class PVE : public other
{
    Q_OBJECT

public:
    explicit PVE(QWidget *parent = nullptr);
    ~PVE();
    void calculateScore();
    void computer();
    void mouseReleaseEvent(QMouseEvent* event);
    void action_NewGame();
    void pushbuttom_again();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PVE *ui;
    int scoreMap[19][19];  //二维数组保存权值
    int JudgeWhoFirst();
    void ComputerFirst();
    std::vector<chessdata> BackChess;   //向量数组表示栈来保存悔棋
    bool computerfirst;
};

#endif // PVE_H
