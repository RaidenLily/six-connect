#ifndef OTHER_H
#define OTHER_H

//�������ڵĻ���

#include <QMainWindow>
#include "gameplay.h"
#include "QPushButton"

class other : public QMainWindow
{
    Q_OBJECT
public:
    explicit other(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent* event);
    void closeEvent(QCloseEvent *);

protected:
    int X,Y;   //��Ϸ��������
    GamePlay *Game;   //��Ϸ�߼�ʵ��
    QColor Color;
    QPushButton *again;   //����һ�̰���

public slots:
    virtual void pushbuttom_again()=0;
    virtual void action_PVPNewGame();
    virtual void action_PVENewGame();
    virtual void action_OnLineNewGame();

private:
    int moveX;
    int moveY;
    int chessnum;
};

#endif // OTHER_H
