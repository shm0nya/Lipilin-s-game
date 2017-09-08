#include "home_windows.h"
#include "ui_home_windows.h"

Home_windows::Home_windows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_windows)
{
    ui->setupUi(this);

}

Home_windows::~Home_windows()
{
    delete ui;
}

void Home_windows::setLogin(const QString& str_login)
{
    login_name = str_login;
    ui->login->setText(str_login);
}
