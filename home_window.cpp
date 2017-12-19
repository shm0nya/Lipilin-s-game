#include "home_window.h"
#include "ui_home_window.h"

#include <QMessageBox>
#include <ctime>
#include <cstdlib>

home_window::home_window(QString login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::home_window)
{
    ui->setupUi(this);
    connect(ui->button_send_messege,SIGNAL(clicked()),this, SIGNAL(change_wnd_to_swnd()));

    srand(time(NULL));//это для случайных чисел

    login_name = login;
    ui->lbl_login_value->setText(login_name);
    ui->lbl_level_value->setText("FiRsT Leeeeevel!!!!!!");
    add_new_player(login_name);

    ui->lbl_new_intercepted_msg->setPixmap(QPixmap::fromImage(QImage(":/images/new_messege.png")).scaled(
                                               ui->lbl_new_intercepted_msg->size()));
    ui->lbl_new_intercepted_msg->setVisible(false);
}

home_window::~home_window()
{
    delete ui;
}

vector <vector<QImage>> cut_image(QImage &image, int n, int m)
{
    vector<vector<QImage>> cut;
    for (int i = 0; i<m; i++)
    {
        vector<QImage> str_image;
        for (int j = 0; j<n; j++)
        {
            QImage temp(100,100,image.format());
            for (int wid = j*100; wid<j*100+100; wid++)
            {
                for (int hei = i*100; hei<i*100+100; hei++)
                {
                    QRgb t = image.pixel(wid,hei);
                    temp.setPixel(wid%100, hei%100, t);
                }
            }
            str_image.push_back(temp);
        }
        cut.push_back(str_image);
    }
  return cut;
}

void home_window::create_img_buttons(vector<vector<QImage>> &cut, int n, int m, vector<vector<QString>> codes)
{
    for (int i = 0; i < n; i++)
    {
        vector<QPB_modify*> pb_vec;
        for (int j = 0; j < m; j++)
        {
            QPB_modify *pb = new QPB_modify;
            pb->reverse_img = cut[i][j];
            pb->i = i;
            pb->j = j;
            pb->rune_code = codes[i][j];
            pb->was_opening = false;

            QSize button_size(50,50);
            pb->setMaximumSize(button_size);
            pb->setMinimumSize(button_size);

            pb->setIcon(QIcon(":/images/question.png"));
            QSize icon_size(40,40);
            pb->setIconSize(icon_size);

            connect(pb, &QPushButton::clicked, [this, pb]()
            {
                if (count_777 == 0)
                {
                    QMessageBox::information(this, "Азино 777", "Вращайте барабан!");
                    return;
                }
                count_777--;

                QPushButton *pb2 = new QPushButton;
                pb2->setIcon(QPixmap::fromImage(pb->reverse_img));
                pb2->setIconSize(pb->size());
                pb2->setMaximumSize(pb->size());
                emit i_opend(pb->reverse_img, pb->i, pb->j, pb->rune_code);
                ui->componate_custom_buttons_img->addWidget(pb2, pb->i, pb->j);
            });

            emit do_it(pb->i, pb->j);
            ui->componate_custom_buttons_img->addWidget(pb,i,j);
            pb_vec.push_back(pb);
        }
        icons.push_back(pb_vec);
    }
}

void home_window::on_pushButton_clicked()
{
    original_img.load(":/images/work image.png");
    cut = cut_image(original_img,5,5);
    //create_img_buttons(cut, 5,5, );
}

void home_window::add_new_player(QString new_player_login)
{
    players.push_back(new_player_login);
    ui->user_list->addItem(new_player_login);
}

void home_window::on_button_overhear_messege_clicked()
{
    ui->lbl_new_intercepted_msg->setVisible(false);
    emit this->show_intercept_wnd_please();
}

void home_window::on_button_inercept_clicked()
{
    QString intercepting_player;
    intercepting_player = ui->edit_overhere->text();

    for (int i = 0; i < int(players.size()); i++)
        if (intercepting_player == players[i])
        {
            emit this->i_want_intercept(intercepting_player);
            ui->lbl_overhere_value->setText(intercepting_player);
            return;
        }

    QMessageBox::information(this, "error", "Такого игрока нет");
}

void home_window::set_visibale_new_messege(bool vis)
{
    ui->lbl_new_intercepted_msg->setVisible(vis);
}


/* ------ */
void home_window::on_automat_clicked()
{
    int luck; //переменная, определяющая, откроется ли картинка

    luck=rand()%10;

    if (luck<7)
    {
        //3 случайные картинки, не совпадающие
        rand_image(1);
        QMessageBox::information(0,"LOSE", "К сожалению, вам не повезло. Попробуйте еще раз.");
    }
    else if (luck<9)
    {
        rand_image(2);
        //открыть 2 одинаковые
        QMessageBox::information(0,"WIN", "Поздравляем! Вы можете открыть одно изображение!");
        count_777++;
    }
    else
    {
        rand_image(3);
        //открыть 3 одинаковые
        QMessageBox::information(0,"WIN", "Вы сказочный везунчик! Вы можете открыть целых два изображения!");
        count_777=+2;
    }
}

void home_window::rand_image(int c)
{
    QImage img;
    int image_num=5, image_num2=5, image_num3=5;

    switch (c) {
    case 3:
        image_num = rand()%5;
        img=runes[image_num];
        ui->rand_image1->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image1->size()));
        ui->rand_image2->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image2->size()));
        ui->rand_image3->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image3->size()));
        break;
    case 2:
        int place;
        place = rand()%3;
        image_num = rand()%5;
        image_num2 = rand()%5;
        while(image_num2==image_num)
        {
            image_num2 = rand()%5;
        }
        switch (place) {
        case 0:
            //натянуть на 2 и 3
            img=runes[image_num];
            ui->rand_image2->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image2->size()));
            ui->rand_image3->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image3->size()));

            img=runes[image_num2];
            ui->rand_image1->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image1->size()));
            break;
        case 1:
            //натянуть на 1 и 3
            image_num = rand()%5;
            img=runes[image_num];
            ui->rand_image1->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image1->size()));
            ui->rand_image3->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image3->size()));

            img=runes[image_num2];
            ui->rand_image2->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image2->size()));
            break;
        case 3:
            //натянуть на 1 и 2
            image_num = rand()%5;
            img=runes[image_num];
            ui->rand_image1->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image1->size()));
            ui->rand_image2->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image2->size()));

            img=runes[image_num2];
            ui->rand_image3->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image3->size()));
            break;
        }


        break;
    default://должен срабатывать при с=1

        image_num = rand()%5;
        image_num2 = rand()%5;
        while(image_num2==image_num)
        {
            image_num2 = rand()%5;
        }
        image_num3 = rand()%5;
        while((image_num3==image_num)||(image_num3==image_num2))
        {
            image_num2 = rand()%5;
        }
        //сделать одно
        img=runes[image_num];
        ui->rand_image1->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image1->size()));
        //второе
        img=runes[image_num2];
        ui->rand_image2->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image2->size()));
        //третье
        img=runes[image_num3];
        ui->rand_image3->setPixmap(QPixmap::fromImage(img).scaled(ui->rand_image3->size()));
        break;
    }
}

void home_window::i_find_image_bf(int i, int j)
{
    QPB_modify *pb = icons[i][j];
    count_777++; // Компенсация перехваченного сообщения
    emit pb->clicked();
}















