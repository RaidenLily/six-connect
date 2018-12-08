#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "pvp.h"
#include "pve.h"
#include "netgame.h"

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_PVP_clicked();
    void on_PVE_clicked();
    void on_online_clicked();

private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H
