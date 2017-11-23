#include "interception.h"
#include "ui_interception.h"

interception::interception(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interception)
{
    ui->setupUi(this);

    // В начале все поясвняющие надписи делаются невидимыми, а кнопка криптографии неактивной

    ui->lbl_p_key_show->setVisible(false);
    ui->lbl_img_show->setVisible(false);
    ui->lbl_s_key_show->setVisible(false);
}

interception::~interception()
{
    delete ui;
}

void interception::on_pushButton_2_clicked()
{
    emit this->homecomig();
}
