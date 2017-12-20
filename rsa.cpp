#include "rsa.h"
#include "ui_rsa.h"

rsa::rsa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rsa)
{
    ui->setupUi(this);
}

rsa::~rsa()
{
    delete ui;
}

void rsa::on_button_rsa_key_generate_2_clicked()
{
    /*генерация ключей
    получаем какой-то ключ
    выводим его в label
    выглядит примерно так:
    ui->rsa_key_2->setText(key);
    */
}

void rsa::on_button_crypto_cansel_2_clicked()
{
    //отменяем все (а оно нам надо?) можно вообще убрать эту кнопку
}

void rsa::on_button_send_messege_clicked()
{
    //отправка сообщения
}

void rsa::on_button_back_clicked()
{
    //назад
}



void rsa::on_button_load_img_2_clicked()
{
    //взяла из send_message. может не работать тут)
    /**/
    QString img_original_puth = QFileDialog::getOpenFileName(
                this,
                tr("Выберите файл"),
                "C:\\",
                "All files (*.*);; Image file (*.bmp)"
                );

    /* Новое изображение загружается
     * После загрузки устанавливаюстя два изображения - оригинальное и "изменяемое"
     * Переменные wid и hei обозначают соответственно ширину и высоту
     * Введены для большей понятности кода */

    Loaded_image.load(img_original_puth);
    flag_new_image = true;
    Encrypted_image = Loaded_image;
    int wid = ui->img_original->width();
    int hei = ui->img_original->height();
    ui->img_original->setPixmap(QPixmap::fromImage(Loaded_image.scaled(wid,hei)));

    int widch = ui->img_changed->width();
    int heich = ui->img_changed->height();
    ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image.scaled(widch,heich)));
}

void rsa::on_button_choose_img_2_clicked()
{

}
