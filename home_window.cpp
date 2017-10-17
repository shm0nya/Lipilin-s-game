#include "home_window.h"
#include "ui_home_window.h"

#include <QMessageBox>

home_window::home_window(QString str_login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::home_window)
{
    ui->setupUi(this);
    connect(ui->button_send_messege,SIGNAL(clicked()),this, SIGNAL(change_wnd_to_swnd()));
}

home_window::~home_window()
{
    delete ui;
}


vector <vector<QImage>> cut_image(QImage &image, int n, int m)
{
    vector<vector<QImage>> cut;
    for (int i = 0; i < n; i++)
    {
        vector<QImage> str_image;
        for (int j = 0; j<m; j++)
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

void home_window::create_img_buttons(vector<vector<QImage>> &cut, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            QPB_modify *pb = new QPB_modify;
            pb->reverse_img = cut[i][j];
            pb->i = i;
            pb->j = j;
            pb->was_opening = false;

            QSize button_size(50,50);
            pb->setMaximumSize(button_size);
            pb->setMinimumSize(button_size);

            pb->setIcon(QIcon(":/images/question.png"));
            QSize icon_size(40,40);
            pb->setIconSize(icon_size);

            connect(pb, &QPushButton::clicked, [this, pb](){
                pb->setIcon(QPixmap::fromImage(pb->reverse_img));
                pb->setIconSize(pb->size());
                pb->setEnabled(false);
                emit i_opend(pb->reverse_img, pb->i, pb->j);
            });

            emit do_it(pb->i, pb->j);
            ui->componate_custom_buttons_img->addWidget(pb,i,j);
        }
}


void home_window::on_pushButton_clicked()
{
    original_img.load(":/images/work image.png");
    vector<vector<QImage>> cut = cut_image(original_img,5,5);
    create_img_buttons(cut, 5,5);
}
