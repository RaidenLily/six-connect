#ifndef GAMEPLAY_H
#define GAMEPLAY_H

struct DrawLine   //Ӯ��֮���ߵĽṹ
{
    int x;
    int y;
};

class GamePlay   //��Ϸ���߼�
{
public:
    GamePlay();
    void people_putdown(int ,int);
    bool judge(int,int);   //�жϵ�ǰ�Ƿ��ǿյģ��ǿշ���true
    int chess[19][19];    //��ά���������
    int JudgeWin(int,int);
    int chessnum;//��¼�µ�������
    bool paint;    //�Ƿ�����
    bool able;     //��Ϸ�Ƿ�ɲ���
    bool full;     //�����Ƿ�����
    bool first;
    int player;
    DrawLine front;    //Ӯ�˵�ʱ���ǻ��ߵ�ͷ��
    DrawLine back;

private:
    bool win1(int,int);
    bool win2(int,int);
    bool win3(int,int);
    bool win4(int,int);
};

#endif // GAMEPLAY_H
