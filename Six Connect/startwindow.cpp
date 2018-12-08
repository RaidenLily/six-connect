#include "startwindow.h"
#include "ui_startwindow.h"

//开始主界面

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_PVP_clicked()
{
    this->close();
    PVP *a=new PVP();
    a->show();
}

void StartWindow::on_PVE_clicked()
{
    this->close();
    PVE *a=new PVE();
    a->show();
}

void StartWindow::on_online_clicked()
{
    this->close();
    NetGame *a=new NetGame();
    a->show();
}
