#ifndef PVP_H
#define PVP_H

#pragma execution_character_set("utf-8")

#include <QMouseEvent>
#include <QTimer>
#include "gameplay.h"
#include "other.h"
#include <vector>

namespace Ui {
class PVP;
}

class PVP : public other
{
    Q_OBJECT

public:
    explicit PVP(QWidget *parent = nullptr);
    ~PVP();
    QTimer *Btimer;
    QTimer *Wtimer;
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *event);
    void action_PVPNewGame();
    void pushbuttom_again();
    void action_PVENewGame();
    void action_OnLineNewGame();


private slots:
    void Blacktimer();
    void Whitetimer();

private:
    Ui::PVP *ui;
    int moveX;
    int moveY;
    int WhiteTimes;
    int BlackTimes;
};

#endif // PVP_H
