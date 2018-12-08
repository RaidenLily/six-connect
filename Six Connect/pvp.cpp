#include "pvp.h"
#include "ui_pvp.h"
#include "QPainter"
#include <QString>
#include <QMessageBox>

//人人对战

PVP::PVP(QWidget *parent) :
    other(parent),
    ui(new Ui::PVP),WhiteTimes(30),BlackTimes(30)
{
    ui->setupUi(this);
    centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    setMouseTracking(true);
    //centralWidget()->setMouseTracking(true);
    Btimer=new QTimer(this);
    Wtimer=new QTimer(this);
    connect(Btimer,SIGNAL(timeout()),this,SLOT(Blacktimer()));
    connect(Wtimer,SIGNAL(timeout()),this,SLOT(Whitetimer()));
    again=new QPushButton("再来一局",this);
    again->setGeometry(980,600,150,50);
    connect(again,SIGNAL(clicked()),this,SLOT(pushbuttom_again()));
    ui->label_2->hide();
    again->hide();
}

PVP::~PVP()
{
    delete ui;
}

void PVP::Blacktimer()   //计时
{
    if(!BlackTimes)
    {
        QMessageBox::about(this,"时间到","黑子输！  ");
        Btimer->stop();
        Game->able=false;
    }
    else
        BlackTimes--;
    update();
}

void PVP::Whitetimer()
{
    if(!WhiteTimes)
    {
        QMessageBox::about(this,"时间到","白子输！  ");
        Game->able=false;
        Wtimer->stop();
    }
    else
        WhiteTimes--;
    update();
}

void PVP::paintEvent(QPaintEvent *event)
{
        other::paintEvent(event);
        QPainter painter(this);
        QBrush brush;
        brush.setColor(Qt::black);
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(1050,180,50,50);
        brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawEllipse(1050,430,50,50);
        QString Btimes=QString("%1").arg(BlackTimes);
        QString Wtimes=QString("%1").arg(WhiteTimes);
        ui->BlackTimer->setText(Btimes);
        ui->WhiteTimer->setText(Wtimes);
}

void PVP::mouseReleaseEvent(QMouseEvent* event)
{
    if(Game->able)
    {
        if(event->x()<30||event->y()<30||event->x()>790||event->y()>790)   //点击棋盘外面无效
            return;
        other::mouseReleaseEvent(event);
        Game->people_putdown(X,Y);
        update();
        switch(Game->JudgeWin(X,Y))
        {
        case 0:
            if(/*Game->chess[X][Y]==2&&*/(Game->player%4)==0)
            {
                Btimer->stop();
                BlackTimes=30;
                Wtimer->start(1000);
                ui->label->hide();
                ui->label_2->show();
            }
            else if(/*Game->chess[X][Y]==1&&*/(Game->player%4)==2)
            {
                Wtimer->stop();
                WhiteTimes=30;
                Btimer->start(1000);
                ui->label->show();
                ui->label_2->hide();
            }
            if(Game->full)
            {
                Wtimer->stop();
                Btimer->stop();
                again->show();
                QMessageBox::about(this,"DRAW","平局!!!");
            }
            break;
        case 1:
            Wtimer->stop();
            Btimer->stop();
            Game->able=false;
            QMessageBox::about(this,"WIN","白子赢!!!");
            again->show();
            break;
        case 2:
            Btimer->stop();
            Wtimer->stop();
            Game->able=false;
            QMessageBox::about(this,"WIN","黑子赢!!!");
            again->show();
            break;
        }
    }
    else
        return;
}

void PVP::action_PVPNewGame()
{
    memset(Game->chess,0,sizeof(Game->chess));
    Game->player=0;
    Game->first=true;
    Btimer->stop();
    Wtimer->stop();
    WhiteTimes=30;
    BlackTimes=30;
    Game->paint=false;
    Game->able=true;
    Game->chessnum=0;
    Game->full=false;
}

void PVP::pushbuttom_again()   //跟上面的开多一局一样
{
    memset(Game->chess,0,sizeof(Game->chess));
    Game->player=0;
    Game->first=true;
    WhiteTimes=30;
    BlackTimes=30;
    Game->paint=false;
    Btimer->stop();
    Wtimer->stop();
    Game->able=true;
    Game->chessnum=0;
    Game->full=false;
}

void PVP::action_PVENewGame()
{
    other::action_PVENewGame();
    Btimer->stop();
    Wtimer->stop();
}

void PVP::action_OnLineNewGame()
{
    other::action_OnLineNewGame();
    Btimer->stop();
    Wtimer->stop();
}
