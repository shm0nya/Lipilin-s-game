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
    // Tab 1:
    login_name = str_login;
    /*--------------------------------------------------------------*/
    // Tab 2:
    ui->Button_Pblok_use->setEnabled(false);
    ui->Button_Sblok_use->setEnabled(false);

}

Home_windows::~Home_windows()
{
    delete ui;
}

/*------------------ TAB 1 ---------------------------------------*/

void Home_windows::on_friend_edit_editingFinished()
{
    /*
     * После того, как ввод пользователем завершен, идет проверка наличия такого человека
     * Проверка того, что не перехватывает у того же, у кого и принимает
     * #!Проверка пока не реализована
     * После этого идёт изменение значения в поле, где показывается информация
     * Затем строка очищается
    */
    ui->friend_show_who_it_value->setText(ui->friend_edit->text());
    ui->friend_edit->clear();
}

void Home_windows::on_opponent_edit_editingFinished()
{
    /*
     * После того, как ввод пользователем завершен, идет проверка наличия такого человека
     * Проверка того, что не перехватывает у того же, у кого и принимает
     * #!Проверка пока не реализована
     * Указывается в атрибуте класса iOverhear, что он прослушивает данного человека
     * После этого идёт изменение значения в поле, где показывается информация
     * Затем строка очищается
    */
    iOverhear = ui->opponent_edit->text();
    ui->opponent_show_is_value->setText(ui->opponent_edit->text());
    ui->opponent_edit->clear();
}

/*----------------- TAB 2 ----------------------------------------*/

/*
 * Изменение для spinBox сделаны через QTDesigner (изменение сигналов и слотов, F4)
*/

void Home_windows::on_P_key_size_slider_valueChanged(int value)
{
    /* У слайдера нельзя задать шаг 2, при перемещении его мышкой,
     * поэтому это делается искусственно.
     * good_value = value + 1 при нечетном, и value + 0 при четном
     * Дополнительно меняет значение счетчика на соответствующее
    */
    int good_value;
    good_value = value+value%2;
    ui->P_key_size_slider->setValue(good_value);
    ui->P_key_size_spinBox->setValue(good_value);
}

void Home_windows::on_S_key_size_slider_valueChanged(int value)
{
    /* Аналогично, как и для P slider
     * У слайдера нельзя задать шаг 2, при перемещении его мышкой,
     * поэтому это делается искусственно.
     * good_value = value + 1 при нечетном, и value + 0 при четном
     * Дополнительно меняет значение счетчика на соответствующее
    */
    int good_value;
    good_value = value+value%2;
    ui->S_key_size_slider->setValue(good_value);
    ui->S_key_size_spinBox->setValue(good_value);
}

void Home_windows::on_P_key_generate_button_clicked()
{
    /* При нажатии проверяет: 1) задано ли генерирующее слово
     *                        2) Длина = 0 или нет
     * В случае не выполнения данных условий - выводи окно ошибки и завершается метод
     *
     * В случае успеха - выводит данные пользователю:label show_now_use...
     * Затем генерирует ключ перестановок, записывает его в атрибут p_key
     * Делает активной клавишу "зашифровать P"
    */
    if (ui->P_key_line_edit->text() == "")
    {
        QMessageBox::information(this,"Error","Не задан ключ P");
        return;
    }

    if (ui->P_key_size_spinBox->value()==0)
    {
        QMessageBox::information(this,"Error","Длина ключа P не может быть = 0");
        return;
    }

    QString new_size = QString("%1").arg(ui->P_key_size_spinBox->value());
    ui->show_now_use_P_size->setText(new_size);
    ui->show_now_use_P_value->setText(ui->P_key_line_edit->text());

    //srand();
    p_key = pblok_key(ui->P_key_size_spinBox->value());

    ui->Button_Pblok_use->setEnabled(true);
}

void Home_windows::on_S_key_generate_button_clicked()
{
    /* При нажатии проверяет: 1) задано ли генерирующее слово
     *                        2) Длина = 0 или нет
     * В случае не выполнения данных условий - выводи окно ошибки и завершается метод
     *
     * #!!! Реализован Виженер, а не SBLOK
     *
     * В случае успеха - выводит данные пользователю:label show_now_use...
     * Затем генерирует ключ перестановок, записывает его в атрибут p_key
     * Делает активной клавишу "Зашифровать S"
    */
    if (ui->S_key_line_edit->text() == "")
    {
        QMessageBox::information(this,"Error","Не задан ключ S");
        return;
    }

    if (ui->S_key_size_spinBox->value()==0)
    {
        QMessageBox::information(this,"Error","Длина ключа S не может быть = 0");
        return;
    }


    QString new_size = QString("%1").arg(ui->S_key_size_spinBox->value());
    ui->show_now_use_S_size->setText(new_size);
    ui->show_now_use_S_value->setText(ui->S_key_line_edit->text());

    //srand();
    s_key = pblok_key(ui->S_key_size_spinBox->value());

    ui->Button_Sblok_use->setEnabled(true);
}

void Home_windows::on_Button_load_origin_img_clicked()
{
    /*
     * Хитрый класс QFileDialog
     * Метод getOpenFileName открывает окошко и позволяет вытащить адрес открываемого файла
     * Принимает в себя параметры:  this - текущее окно
     *                              tr("Open File") - Заголовок в окне
     *                              "C://" по идее должна быть папка по умолчанию. Иначе в том месте, где запущена программа
     *                              Типы файлов, указывается ->  название+маска
    */

    img_original_puth = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*);; Image file (*.bmp)"
                );
}
