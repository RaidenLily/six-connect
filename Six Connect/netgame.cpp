#include "netgame.h"
#include "ui_netgame.h"
#include "QtMultimedia/QSound"

#define chessone ":/Music/Music/chessone.wav"
#define win ":/Music/Music/win.wav"
#define lost ":/Music/Music/lost.wav"

#pragma execution_character_set("utf-8")

NetGame::NetGame(QWidget *parent) :
    other(parent),
    ui(new Ui::NetGame)
{
    ui->setupUi(this);
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
    udpSocket=new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost,45454,QUdpSocket::ReuseAddressHint);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(get_Message()));
    if(ChooseFirst()==QMessageBox::Yes)   //判断谁先
    {
        text1="第一: ";
        ui->wait->hide();
        color=Qt::blue;
        isfirst=true;
    }
    else
    {
        text1="第二: ";
        Game->able=false;
        ui->toyou->hide();
        color=Qt::black;
        isfirst=false;
    }
}

int NetGame::ChooseFirst()
{
    QMessageBox box(QMessageBox::Question,"选择","你是 ?");
    box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box.setButtonText(QMessageBox::Yes,"第一");
    box.setButtonText(QMessageBox::No,"第二");
    return box.exec();
}

NetGame::~NetGame()
{
    delete ui;
}

inline QDataStream &operator<<(QDataStream &DS,SENDER_DATA &SD)   //重载，自定义的结构体直接输入到数据流
{
    DS<<SD.x<<SD.y;
    return DS;
}

inline QDataStream &operator>>(QDataStream &DS,SENDER_DATA &SD)
{
    DS>>SD.x>>SD.y;
    return DS;
}

void NetGame::on_SendMessage_clicked()
{
    QString a=ui->textEdit->toPlainText();
    if(a.isEmpty())  //聊天框输入不能空
    {
        ui->textEdit->setPlaceholderText("输入不能为空 !");
        return;
    }
    ui->textEdit->setPlaceholderText(NULL);   //去除placehold的文字
    send_message(Message1);
    ui->textEdit->clear();
}

void NetGame::get_Message()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray a;
        a.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(a.data(),a.size());
        QDataStream out(&a,QIODevice::ReadOnly);
        int type;
        SENDER_DATA c;
        QString text;
        out>>type;
        QColor color1;
        switch(type)
        {
        case Message1:
            out>>text>>color1;
            ui->textBrowser->setTextColor(color1);
            ui->textBrowser->append(text);
            break;
        case Game1:
            out>>c;
            Game->people_putdown(c.x,c.y);
            if(Game->JudgeWin(c.x,c.y))
            {
                if(Game->JudgeWin(c.x,c.y)==isfirst+1)
                {
                    update();
                    QSound::play(win);
                    QMessageBox::about(this,"WIN","你赢了!!!   ");
                    Game->able=false;
                    ui->toyou->hide();
                    ui->wait->hide();
                    return;
                }
                else
                {
                    update();
                    QSound::play(lost);
                    QMessageBox::about(this,"LOST","你输了!!!   ");
                    Game->able=false;
                    ui->toyou->hide();
                    ui->wait->hide();
                    return;
                }
            }
            if(isfirst)
            {
                if(Game->player%4>=2)
                {
                    Game->able=true;
                    ui->toyou->show();
                    ui->wait->hide();
                }
                else
                {
                    Game->able=false;
                    ui->toyou->hide();
                    ui->wait->show();
                }
            }
            else
            {
                if(Game->player%4<=1)
                {
                    Game->able=true;
                    ui->toyou->show();
                    ui->wait->hide();
                }
                else
                {
                    Game->able=false;
                    ui->toyou->hide();
                    ui->wait->show();
                }
            }
            update();
            break;
        }
        if(Game->full)
        {
            update();
            ui->toyou->hide();
            ui->wait->hide();
            Game->able=false;
            QMessageBox::about(this,"DRAW","平局!!!");
            return;
         }
    }
}

void NetGame::mouseReleaseEvent(QMouseEvent *event)
{
    if(Game->able)
    {
        if(event->x()<30||event->y()<30||event->x()>790||event->y()>790)
            return;
        other::mouseReleaseEvent(event);
        if(Game->judge(X,Y))
            send_message(Game1);
        update();
    }
}

void NetGame::send_message(MessageType type)
{
    QString a=ui->textEdit->toPlainText();
    a=text1+a;
    QByteArray datagram;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out<<type;
    switch (type)
    {
        case Message1:
             out<<a<<color;   //把文字和颜色都发送过去
             break;
        case Game1:
             other_message.x=X;
             other_message.y=Y;
             out<<other_message;
             break;
    }
    udpSocket->writeDatagram(datagram,datagram.length(),QHostAddress::Broadcast,45454);
}

void NetGame::pushbuttom_again()
{
     //单纯定义other类的纯虚函数
}
