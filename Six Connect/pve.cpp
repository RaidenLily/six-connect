#include "pve.h"
#include "ui_pve.h"
#include "QMessageBox"
#include "iostream"
#include <ctime>

PVE::PVE(QWidget *parent) :
    other(parent),
    ui(new Ui::PVE)
{
    ui->setupUi(this);
    memset(scoreMap,0,sizeof(scoreMap));
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
    again=new QPushButton("����һ��",this);
    again->setGeometry(989,530,141,41);
    connect(again,SIGNAL(clicked()),this,SLOT(pushbuttom_again()));
    again->hide();   //��һ����ɺ�����ʾ
    if(JudgeWhoFirst()==QMessageBox::Yes)
    {
        computerfirst=true;
        computer();
    }
    else
    {
        computerfirst=false;
    }
}

int PVE::JudgeWhoFirst()
{
    QMessageBox box(QMessageBox::Question,"ѡ��","˭�� ��");
    box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box.setButtonText(QMessageBox::Yes,"������");
    box.setButtonText(QMessageBox::No,"����");
    return box.exec();
}

PVE::~PVE()
{
    delete ui;
}

void PVE::ComputerFirst()
{
    computer();
}

//�����Ⱦͱ��ֽ��������Ժ��־ͱ��ַ���
void PVE::calculateScore()   //����ÿ����Ȩֵ��������ĵ���������ĵ�ķֽ������
{
    int personNum=0; // ��һ���������ӵĸ���
    int botNum=0; // ���Ի���������ӵĸ���
    int emptyNum=0; // ������հ�λ�ĸ���

    for(int row=0;row<19;row++)
        for(int col=0;col<19;col++)
        {
            // �հ׵����
            if(row>0&&col>0&&Game->chess[row][col]==0)
            {
                for(int y=-1;y<1;y++)   // �����˸�����
                    for(int x=-1;x<=1;x++)
                    {
                        personNum=0;
                        botNum=0;
                        emptyNum=0;
                        if(!(y==0&&x==0))   // ԭ���겻��
                        {
                            for(int i=1;i<=5;i++)
                            {
                                if(row+i*y>=0&&row+i*y<19&&col+i*x>=0
                                        &&col+i*x<19&&Game->chess[row+i*y][col+i*x]==1)
                                    personNum++;
                                else if(row+i*y>=0&&row+i*y<19&&col+i*x>=0
                                        &&col+i*x<19&&Game->chess[row+i*y][col+i*x]==0) // �հ�λ
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                    break;
                            }
                            for(int i=1;i<=5;i++)
                            {
                                if (row-i*y>=0&&row-i*y<19&&col-i*x>=0
                                        &&col-i*x<19&&Game->chess[row-i*y][col-i*x]==1)
                                    personNum++;
                                else if (row-i*y>=0&&row-i*y<19&&col-i*x>=0
                                         &&col-i*x<19&&Game->chess[row-i*y][col-i*x]==0) // �հ�λ
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                    break;
                            }

                            if(personNum==1)                      // ɱ��
                                scoreMap[row][col]+=10;
                            else if(personNum==2)                 // ɱ��
                            {
                                if(emptyNum==1)   //empty=1��һ�˱�����
                                    scoreMap[row][col]+=30;
                                else if(emptyNum==2)   //empty=2���߶���
                                    scoreMap[row][col]+=40;
                            }
                            else if(personNum==3)                 // ɱ��
                            {
                                if(emptyNum==1)
                                    scoreMap[row][col]+=50;
                                else if(emptyNum==2)
                                    scoreMap[row][col]+=100;
                            }
                            else if(personNum==4)
                            {
                                if(emptyNum==1)
                                    scoreMap[row][col]+=1010;
                                else if(emptyNum==2)
                                    scoreMap[row][col]+=2020;
                            }
                            else if(personNum==5)
                                scoreMap[row][col]+=10100;



                            emptyNum=0;



                            for(int i=1;i<=5;i++)
                            {
                                if(row+i*y>=0&&row+i*y<19&&col+i*x>=0
                                        &&col+i*x<19&&Game->chess[row+i*y][col+i*x]==2)
                                    botNum++;
                                else if(row+i*y>=0&&row+i*y<19&&col+i*x>=0
                                        &&col+i*x<19&&Game->chess[row+i*y][col+i*x]==0)
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                    break;
                            }
                            for(int i=1;i<=5;i++)
                            {
                                if(row-i*y>=0&&row-i*y<19&&col-i*x>=0
                                        &&col-i*x<19&&Game->chess[row-i*y][col-i*x]==2)
                                    botNum++;
                                else if(row-i*y>=0&&row-i*y<19&&col-i*x>=0
                                        &&col-i*x<19&&Game->chess[row-i*y][col-i*x]==0) // �հ�λ
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // ���߽�
                                    break;
                            }

                            if(botNum==1)                 // ���
                                scoreMap[row][col]+=10;
                            else if(botNum==2)
                            {
                                if(emptyNum==1)                // ����
                                    scoreMap[row][col]+=45;
                                else if(emptyNum==2)
                                    scoreMap[row][col]+=55;  // ����
                            }
                            else if(botNum==3)
                            {
                                if(emptyNum==1)                // ����
                                    scoreMap[row][col]+=70;
                                else if(emptyNum==2)
                                    scoreMap[row][col]+=120; // ����
                            }
                            else if(botNum==4)
                            {
                                if(emptyNum==1)
                                    scoreMap[row][col]+=1200;
                                else if(emptyNum==2)
                                    scoreMap[row][col]+=10200;
                             }
                            else if(botNum==5)        // ����
                                scoreMap[row][col]+=22000;
                        }
                    }
            }
        }
}

void PVE::computer()
{
    int MAX=0;
    chessdata CD;
    calculateScore();   //��������
    for(int row=0;row<19;row++)//���������ֵ
        for(int col=0;col<19;col++)
            if(Game->chess[row][col]==0)
            {
                if(scoreMap[row][col]>MAX)
                {
                    MAX=scoreMap[row][col];
                    CD.x=row;
                    CD.y=col;
                    CD.computer=true;
                }
            }
    if(MAX==0)
    {
        std::srand(time(NULL));   //MAXΪ0���������֣������Ⱦ��������
        CD.x=std::rand()%19;
        CD.y=std::rand()%19;
    }
    Game->people_putdown(CD.x,CD.y);
    BackChess.push_back(CD);  //ѹ��ջ
    if(Game->JudgeWin(CD.x,CD.y))
    {
        ui->pushButton->hide();
        again->show();
        QMessageBox::about(this,"WIN","����Ӯ!!!");
        Game->able=false;
    }
    else if(Game->full)
    {
        QMessageBox::about(this,"DRAW","ƽ��!!!");
        ui->pushButton->hide();
        again->show();
        Game->able=false;
    }
    update();
}

void PVE::mouseReleaseEvent(QMouseEvent* event)
{
    if(Game->able)
    {
        if(event->x()<30||event->y()<30||event->x()>790||event->y()>790)   //�����������Ч
            return;
        other::mouseReleaseEvent(event);
        if(!Game->judge(X,Y))
            return;
        Game->people_putdown(X,Y);
        update();
        switch(Game->JudgeWin(X,Y))
        {
            case 0:
                chessdata CD;
                CD.x=X;
                CD.y=Y;
                CD.computer=false;
                BackChess.push_back(CD);
                if(Game->full)
                {
                    QMessageBox::about(this,"DRAW","ƽ��!!!");
                    ui->pushButton->hide();
                    again->show();
                    return;
                }
                if(computerfirst)
                {
                    while((Game->player%4)>=2&&Game->able)
                        computer();
                }
                else
                {
                    while((Game->player%4)<2&&Game->able)
                        computer();
                }
                break;
            case 1:
            case 2:
                Game->able=false;
                Game->paint=false;
                QMessageBox::about(this,"WIN","��Ӯ��!!!");
                ui->pushButton->hide();
                again->show();
                break;
        }
    }
    return;
}

void PVE::action_NewGame()
{
    memset(scoreMap,0,sizeof(scoreMap));
    memset(Game->chess,0,sizeof(Game->chess));
    Game->player=0;
    Game->first=true;
    Game->paint=false;
    Game->able=true;
    Game->chessnum=0;
    Game->full=false;
    ui->pushButton->show();
    again->hide();
    BackChess.clear();
    if(computerfirst)
        computer();
    update();
}

void PVE::pushbuttom_again()
{
    memset(scoreMap,0,sizeof(scoreMap));
    memset(Game->chess,0,sizeof(Game->chess));
    Game->player=0;
    Game->first=true;
    Game->paint=false;
    Game->able=true;
    Game->chessnum=0;
    Game->full=false;
    ui->pushButton->show();
    again->hide();
    BackChess.clear();
    if(computerfirst)
        computer();
    update();
}

void PVE::on_pushButton_clicked()   //����
{
    if(BackChess.size()==1||BackChess.empty())
        QMessageBox::about(this,"Empty!    ","�Ѿ�û�û�����!!!");
    else if(BackChess.back().computer)
        for(int i=1;i<=3;i++)   //��ջ�������������ڵ���ʱ��ֱ�������������
        {
            chessdata CD;
            CD = BackChess.back();
            Game->chess[CD.x][CD.y]=0;
            BackChess.pop_back();
            Game->player--;
            if(BackChess.empty())
            {
                Game->first=true;
                Game->player=0;
            }
            Game->chessnum--;   //�µ���������1
        }
    else
    {
        chessdata CD;
        CD = BackChess.back();
        Game->chess[CD.x][CD.y]=0;
        BackChess.pop_back();
        Game->player--;
        Game->chessnum--;
    }
    update();
}
