#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Login_button->setEnabled(false);
    QRegExp is_login_variable("[a-zA-Z0-9]{1,20}");
    ui->login_edit->setValidator(new QRegExpValidator(is_login_variable, this));
    connect(ui->login_edit,SIGNAL(textChanged(QString)),this,SLOT(ok_enabled()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rootwindow()
{
    rootWnd = new root_window;
    rootWnd->show();
    this->close();
}

void MainWindow::playerwindow()
{
    QString name_login = ui->login_edit->text();

    hWnd = new home_window(name_login);
    smWnd = new send_messege;
    ch_bWnd = new choose_button;

    connect(smWnd, SIGNAL(show_ch_buttons_sign()), this, SLOT(show_ch_wnd()));
    connect(smWnd, SIGNAL(change_wnd_to_homewnd()), this, SLOT(sendmess_wnd__home_wnd()));
    connect(hWnd, SIGNAL(change_wnd_to_swnd()),this ,SLOT(home_wnd__sendmess_wnd()));

    connect(hWnd, SIGNAL(do_it(int, int)), this, SLOT(create_pb(int, int)));
    connect(hWnd, SIGNAL(i_opend(QImage, int, int)), this, SLOT(then_opend_img(QImage, int, int)));
    connect(ch_bWnd, SIGNAL(close_wnd()), this, SLOT(if_close_wnd()));
    connect(ch_bWnd, SIGNAL(i_choose_img(QImage)),this ,SLOT(then_choosen_img(QImage)));
    connect(ch_bWnd, SIGNAL(rejected()), this, SLOT(if_close_wnd()));

    hWnd->show();
    this->close();
}



void MainWindow::ok_enabled()
{
    ui->Login_button->setEnabled(ui->login_edit->hasAcceptableInput());
}

void MainWindow::on_Login_button_clicked()
{   
    if(ui->login_edit->text() == "root")
        rootwindow();
    else
        playerwindow();
}

void MainWindow::home_wnd__sendmess_wnd()
{
    hWnd->close();
    smWnd->show();
}

void MainWindow::sendmess_wnd__home_wnd()
{
    smWnd->close();
    hWnd->show();
}

void MainWindow::show_ch_wnd()
{
    smWnd->setEnabled(false);
    ch_bWnd->show();
}

void MainWindow::create_pb(int i, int j)
{
    QPB_modify *pb = new QPB_modify;
    QSize button_size(50,50);
    pb->setMaximumSize(button_size);
    pb->setMinimumSize(button_size);

    pb->setIcon(QIcon(":/images/question.png"));
    QSize icon_size(40,40);
    pb->setIconSize(icon_size);

    connect(pb, &QPushButton::clicked, [this, pb](){
        if (pb->reverse_img.isNull())
            QMessageBox::information(this,"Oops", "Я же говорил, что ничего не будет");
        else
            emit ch_bWnd->i_choose_img(pb->reverse_img);
    });

    ch_bWnd->set_button(pb, i, j);
}

void MainWindow::then_choosen_img(QImage img)
{
    smWnd->user_choose_img(img);
    smWnd->setEnabled(true);
    smWnd->show();
}

void MainWindow::then_opend_img(QImage img, int i, int j)
{
    ch_bWnd->open_button(img, i, j);
}

void MainWindow::if_close_wnd()
{
    smWnd->setEnabled(true);
    smWnd->show();
}

vector<QRgb> PaintPicture (vector<QRgb> &data, QRgb &color)
//позаимствовала и видоизменила функцию шифрования
//пусть будет просто цвет, а в вызове функции укажем, какой именно элемент массива цветов надо брать
{
        //выпиливаем изначально нужный цвет
        QColor paint=QColor(color);
        int red=paint.red;
        int green=paint.green;
        int blue=paint.blue;

        for (int i = 0; i < data.size(); i++)
        {
            // Способ работы с пикселем - QColor
            QColor temp = QColor(data[i]);

            //исключаем белый цвет (фон букв)

            if (!(temp.red = 255 && temp.green = 255 && temp.blue = 255))
            {
                temp.red=red;
                temp.green=green;
                temp.blue=blue;
            }

            data[i] = temp.rgb();

        }
}



