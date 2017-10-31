#include "root_window.h"
#include "ui_root_window.h"

root_window::root_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::root_window)
{
    ui->setupUi(this);

    QRegExp is_int("[0-9]{0,3}");
    ui->edit_n->setValidator(new QRegExpValidator(is_int, this));
    ui->edit_m->setValidator(new QRegExpValidator(is_int, this));

    this->on_button_default_clicked();
}

root_window::~root_window()
{
    delete ui;
}

void root_window::on_button_apply_clicked()
{
    if ((ui->edit_m->text() == "") || (ui->edit_n->text() == ""))
    {
        QMessageBox::information(this, "Error", "Вы не указали один из параметров n, m");
        return;
    }

    // Удаление элементов, при задании новых n, m
    QLayoutItem *ch;
    while ((ch = ui->componate_alphabet_buttons->takeAt(0))!= 0)
    {
            ui->componate_alphabet_buttons->removeItem(ch);
            ch->widget()->deleteLater();
            delete ch;
    }

    flag_default = false;
    n = ui->edit_n->text().toInt();
    m = ui->edit_m->text().toInt();
    create_images();
}

void root_window::create_images()
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            emit this->get_rune(j + i*n);

            QPB_modify *pb = new QPB_modify;
            pb->i = i;
            pb->j = j;
            if (flag_default == true)
                pb->str = messege[j + i*n];

            pb->reverse_img = temp_rune;
            QSize button_size(50,50);
            pb->setMaximumSize(button_size);
            pb->setMinimumSize(button_size);

            pb->setIcon(QIcon(QPixmap::fromImage(temp_rune)));
            QSize icon_size(pb->size());
            pb->setIconSize(icon_size);

            connect(pb, &QPushButton::clicked, [this, pb](){
                emit this->show_make_img_with_my_img(pb->reverse_img, pb->i, pb->j);
            });
            ui->componate_alphabet_buttons->addWidget(pb, i, j);
        }
}

void root_window::on_button_default_clicked()
{
    n = 5;
    m = 5;
    flag_default = true;
    create_images();

    ui->edit_m->setText("5");
    ui->edit_n->setText("5");
}


void root_window::on_pushButton_clicked()
{
    QMessageBox::information(this, "", "запускает старт игры + работу с сетью, которую я прокрастинирую");
}

void root_window::set_rune_at_GL(QPB_modify *pb, int i, int j)
{
    ui->componate_alphabet_buttons->addWidget(pb, i, j);
}
