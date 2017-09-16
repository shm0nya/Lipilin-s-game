#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Login_button, SIGNAL(clicked()), this, SLOT(Login()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Login()
{
    QString name_login = ui->TextLogin->text();
    sWindow = new Home_windows(name_login);
    //sWindow -> setLogin(name_login);
    sWindow->show();  // Показываем основное окно
    this->close();
}
