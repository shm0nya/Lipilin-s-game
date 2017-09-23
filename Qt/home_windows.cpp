#include "home_windows.h"
#include "ui_home_windows.h"

#include <fun.h>

#include <QBuffer>
#include <QFile>
#include <QString>

#include <QFileDialog>

Home_windows::Home_windows(QString str_login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_windows)
{
    ui->setupUi(this);
}

Home_windows::~Home_windows()
{
    delete ui;
}


void Home_windows::on_button_send_messege_clicked()
{
    send_messege_window.show();
}
