#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "home_window.h"
#include "send_messege.h"
#include "choose_button.h"

extern QString name_login;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void ok_enabled();
    void on_Login_button_clicked();

    void home_wnd__sendmess_wnd();
    void sendmess_wnd__home_wnd();
    void create_pb(int i, int j);
    void show_ch_wnd();
    void then_opend_img(QImage img, int i, int j);
    void if_close_wnd();
    void then_choosen_img(QImage img);

private:
    Ui::MainWindow *ui;
    home_window *hWnd;
    send_messege *smWnd;
    choose_button *ch_bWnd;
};

#endif // MAINWINDOW_H
