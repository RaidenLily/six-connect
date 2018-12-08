#include "other.h"
#include "QPainter"
#include "QMouseEvent"
#include "QMessageBox"
#include "QMenu"
#include "QAction"
#include "QMenuBar"
#include "pvp.h"
#include "pve.h"
#include "netgame.h"

other::other(QWidget *parent) : QMainWindow(parent),X(0),Y(0),Color(Qt::green),chessnum(0)
{
    QPalette palette;
    palette.setColor(QPalette::Background,QColor("#B1723C"));
    this->setPalette(palette);
    Game=new GamePlay();
    QMenu *Menu=new QMenu("菜单",this);
    QMenu *newgame=new QMenu("新游戏",this);
    QAction *PVP=new QAction("PVP",this);
    QAction *PVE=new QAction("PVE",this);
    QAction *OnLine=new QAction("OnLine",this);
    newgame->addAction(PVP);
    newgame->addAction(PVE);
    newgame->addAction(OnLine);
    QMenuBar *menu=this->menuBar();
    Menu->addMenu(newgame);
    menu->addMenu(Menu);
    connect(PVP,SIGNAL(triggered()),this,SLOT(action_PVPNewGame()));
    connect(PVE,SIGNAL(triggered()),this,SLOT(action_PVENewGame()));
    connect(OnLine,SIGNAL(triggered()),this,SLOT(action_OnLineNewGame()));
    Game->able=true;
}

void other::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPen pen;
    pen.setColor(QColor("#8D5822"));
    pen.setWidth(7);
    painter.setPen(pen);
    QBrush brush;
    brush.setColor(QColor("#EEC085"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(40,40,740,740);
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    for(int i=0;i<19;i++)
        {
            painter.drawLine(50+i*40,50,50+i*40,770); //画棋盘
            painter.drawLine(50,50+i*40,770,50+i*40);
        }
    if(Game->able==false)
        Color=Qt::gray;
    else
        Color=Qt::green;
    pen.setColor(Color);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(moveX*40+50,moveY*40+50),18,18);
    for(int i=0;i<19;i++)   //遍历数组，下棋
        for(int t=0;t<19;t++)
        {
            if(Game->chess[i][t]==1)
            {
                pen.setColor(Qt::black);
                brush.setColor(Qt::white);
                pen.setWidth(1);
                painter.setPen(pen);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(i*40+50,t*40+50),18,18);
            }
            else if(Game->chess[i][t]==2)
            {
                pen.setColor(Qt::black);
                brush.setColor(Qt::black);
                pen.setWidth(1);
                painter.setPen(pen);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint(i*40+50,t*40+50),18,18);
            }
        }
    if(Game->paint)   //赢后标记连线
    {
        pen.setColor(Qt::red);
        pen.setWidth(5);
        painter.setPen(pen);
        painter.drawLine(50+Game->front.x*40,50+Game->front.y*40,50+Game->back.x*40,50+Game->back.y*40);
    }
}

void other::mouseMoveEvent(QMouseEvent *event)   //鼠标移动会有标识
{
    moveX=(event->x()-30)/40;
    moveY=(event->y()-30)/40;
    if(moveX<0)
        moveX=0;
    if(moveY<0)
        moveY=0;
    if(moveX>18)
        moveX=18;
    if(moveY>18)
        moveY=18;
    update();
}

void other::mouseReleaseEvent(QMouseEvent* event)
{
        X = (event->x()-30)/40;
        Y = (event->y()-30)/40;
}

void other::closeEvent(QCloseEvent *event)  //试图关窗口会有提示
{
    QMessageBox box(QMessageBox::Question,"确定","退出 ?");
    box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box.setDefaultButton(QMessageBox::No);
    int a=box.exec();
    if(a==QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void other::action_PVPNewGame()//菜单栏的设置
{
    this->close();
    PVP *a=new PVP();
    a->show();
}

void other::action_PVENewGame()
{
    this->close();
    PVE *a=new PVE();
    a->show();
}

void other::action_OnLineNewGame()
{
    this->close();
    NetGame *a=new NetGame();
    a->show();
}
