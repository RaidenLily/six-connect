#ifndef NETGAME_H
#define NETGAME_H

#include <QtNetwork>
#include "QMessageBox"
#include "other.h"
#include "string"
#include "QMouseEvent"
#include "QColor"

enum MessageType{Message1,Game1};

struct SENDER_DATA
{
    int x;
    int y;
};

namespace Ui {
class NetGame;
}

class NetGame : public other
{
    Q_OBJECT

public:
    explicit NetGame(QWidget *parent = nullptr);
    ~NetGame();
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_SendMessage_clicked();
    void get_Message();

private:
    Ui::NetGame *ui;
    QUdpSocket *udpSocket;
    int ChooseFirst();
    SENDER_DATA other_message;
    void send_message(MessageType type);
    QString text1;
    QColor color;   //聊天的字体颜色
    void pushbuttom_again();
    bool netgamefirst;
    bool isfirst;
};

#endif // NETGAME_H
