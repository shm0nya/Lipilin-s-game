#include "send_messege.h"
#include "ui_send_messege.h"

send_messege::send_messege(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::send_messege)
{
    ui->setupUi(this);
    ui->button_crypto_p->setEnabled(!p_key.empty());
    ui->button_crypto_s->setEnabled(!s_key.empty());
}

send_messege::~send_messege()
{
    delete ui;
}

void send_messege::on_p_key_size_edit_slider_valueChanged(int value)
{
    /*
     * Длина ключа должна быть кратной 2
     * Длина ключа задается двумя элементами: slider, spinbox
     * При смене значения на слайдере значения увеличивается до четного (или нет)
    */
    int good_value = value + value%2;
    ui->p_key_size_edit_slider->setValue(good_value);
    ui->p_key_size_edit_spbox->setValue(good_value);
}

void send_messege::on_s_key_size_edit_slider_valueChanged(int value)
{
    /*
     * Смотри: void send_messege::on_p_key_size_edit_slider_valueChanged(int value)
    */
    int good_value = value + value%2;
    ui->s_key_size_edit_slider->setValue(good_value);
    ui->s_key_size_edit_spbox->setValue(good_value);
}

void send_messege::on_button_load_img_clicked()
{
        /*
         * Хитрый класс QFileDialog
         * Метод getOpenFileName открывает окошко и позволяет вытащить адрес открываемого файла
         * Принимает в себя параметры:  this - текущее окно
         *                              tr("Open File") - Заголовок в окне
         *                              "C://" по идее должна быть папка по умолчанию. Иначе в том месте, где запущена программа
         *                              Типы файлов, указывается ->  название+маска
        */

        QString img_original_puth = QFileDialog::getOpenFileName(
                    this,
                    tr("Выберите файл"),
                    "C:\\",
                    "All files (*.*);; Image file (*.bmp)"
                    );

        /*
         * Новое изображение загружается
         *
         * #! При загрузке старое должно стиратсья - не реализовано
         *
         * Переменные wid и hei обозначают соответственно ширину и высоту
         * Введены для большей понятности кода
        */

        Loaded_image.load(img_original_puth);
        Encrypted_image = Loaded_image;
        int wid = ui->img_original->width();
        int hei = ui->img_original->height();
        ui->img_original->setPixmap(QPixmap::fromImage(Loaded_image.scaled(wid,hei)));
}

void send_messege::on_button_p_key_generate_clicked()
{
    /* При нажатии проверяет: 1) задано ли генерирующее слово
     *                        2) Длина = 0 или нет
     * В случае не выполнения данных условий - выводи окно ошибки и завершается метод
     *
     * В случае успеха - выводит данные пользователю:label show_now_use...
     * Затем генерирует ключ перестановок, записывает его в атрибут p_key
     * Делает активной клавишу "зашифровать P"
    */
    if (ui->p_key_edit->text() == "")
    {
        QMessageBox::information(this,"Error","Не задан ключ P");
        return;
    }

    if (ui->p_key_size_edit_spbox->value()==0)
    {
        QMessageBox::information(this,"Error","Длина ключа P не может быть = 0");
        return;
    }

    p_key = pblok_key(ui->p_key_size_edit_spbox->value());
    ui->button_crypto_p->setEnabled(true);

    QString str = QString("%1").arg(ui->p_key_size_edit_spbox->value());// Перевод int в строку
    ui->lbl_p_key_size->setText(str);
    ui->lbl_p_key_value->setText(ui->p_key_edit->text());
}

void send_messege::on_button_s_key_generate_clicked()
{
    /* При нажатии проверяет: 1) задано ли генерирующее слово
     *                        2) Длина = 0 или нет
     * В случае не выполнения данных условий - выводи окно ошибки и завершается метод
     *
#!   * #!!! Реализован Виженер, а не SBLOK
     *
     * В случае успеха - выводит данные пользователю:label show_now_use...
     * Затем генерирует ключ перестановок, записывает его в атрибут p_key
     * Делает активной клавишу "Зашифровать S"
    */
    if (ui->s_key_edit->text() == "")
    {
        QMessageBox::information(this,"Error","Не задан ключ S");
        return;
    }

    if (ui->s_key_size_edit_spbox->value()==0)
    {
        QMessageBox::information(this,"Error","Длина ключа S не может быть = 0");
        return;
    }

    s_key = sblok_like_vigener_key(ui->s_key_size_edit_spbox->value());
    ui->button_crypto_s->setEnabled(true);

    QString str = QString("%1").arg(ui->s_key_size_edit_spbox->value());// Перевод int в строку
    ui->lbl_s_key_size->setText(str);
    ui->lbl_s_key_value->setText(ui->s_key_edit->text());
}

void send_messege::on_button_save_img_clicked()
{
    /*
     * Метод getExistingDirectory, работает аналогично getOpenFileName
     * (см: void Home_windows::on_Button_load_origin_img_clicked() или документацию (F1))
    */
    QString img_save_puth_to_dir = QFileDialog::getExistingDirectory(
                this,
                tr("Выберите директорию"),
                "C:\\"
                );
}


void send_messege::on_button_crypto_p_clicked()
{
    /*
     * Сначал идет проверка, загружено ли изображение.
     * Если нет - выдается сообщение об ошибке.
     *
     * Каждый пиксель задается своими координтами: высота и ширина.
     * Используется цикл со счетчиком count от нуля до Высота*Ширина изображения.
     * QImage.pixel(wid,hei)=Qmage.pixel(целая часть от деления count на ширину,
     *                                      остаток от деления count на ширину)
     *
     * Считывается блок пикселей размером с длину блока, заданную пользователем,
     * перемешивается, после чего записывается обратно в изображение.
     *
     * После обработки добавляет букву "P" в алгоритм
     * Устанавливает зашифрованную картинку на экран
    */

    if(Loaded_image.isNull())
    {
        QMessageBox::information(this,"Error","Вы не загрузили изображение.");
         return;
    }

    // Инициируются переменные для удобства использования
    int wid = Encrypted_image.width();
    int hei = Encrypted_image.height();
    int p_size = p_key.size();

    for (int i = 0; i < hei*wid;)
    {

        // Считывание и шифрование
        vector<QRgb> temp;
        for (int j=0; j<p_size; j++)
        {
            QRgb t;
            t=Encrypted_image.pixel(i%wid, i/wid);
            temp.push_back(t);
            i++;
        }

        // Шифроание и запись зашифрованных пикселей
        if (temp.size()==p_size)
        {
            temp = use_pblok(temp, p_key);
            for (int j = 0; j<p_size;j++)
            {
                int k=i-p_size+j;
                Encrypted_image.setPixel(k%wid, k/wid, temp[j]);
            }
        }
    }

    QString new_algoritm = ui->lbl_algoritm_value->text() + "P";
    ui->lbl_algoritm_value->setText(new_algoritm);

    int lblwid = ui->img_changed->width();
    int lblhei = ui->img_changed->height();

    ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image).scaled(lblwid,lblhei));
}

void send_messege::on_button_crypto_s_clicked()
{
    if(Loaded_image.isNull())
    {
        QMessageBox::information(this,"Error","Вы не загрузили изображение.");
         return;
    }

    int wid = Encrypted_image.width();
    int hei = Encrypted_image.height();
    int blok_size = s_key.size();

    // Считывание
    for (int i = 0; i < hei*wid;)
    {
        vector<QRgb> temp;
        for (int j=0; j<blok_size; j++)
        {
            QRgb t;
            t=Encrypted_image.pixel(i%wid, i/wid);
            temp.push_back(t);
            i++;
        }

        // Шифроание и запись зашифрованных пикселей
        if (temp.size()==blok_size)
        {
            temp = sblok_like_vigener(temp, s_key);
            for (int j = 0; j<blok_size;j++)
            {
                int k=i-blok_size+j;
                Encrypted_image.setPixel(k%wid, k/wid, temp[j]);
            }
        }
    }

    QString new_algoritm = ui->lbl_algoritm_value->text() + "S";
    ui->lbl_algoritm_value->setText(new_algoritm);

    int lblwid = ui->img_changed->width();
    int lblhei = ui->img_changed->height();

    ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image).scaled(lblwid,lblhei));
}

void send_messege::on_button_algoritm_crypto_clicked()
{
    /*
     * На сегодня не реализовано
    */
    QMessageBox::information(this,"sorry","Нереализовано");
}

void send_messege::on_button_paint_clicked()
{
    QMessageBox::information(this,"sorry","Нереализовано");
}

void send_messege::on_button_crypto_cansel_clicked()
{
    QMessageBox::information(this,"sorry","Нереализовано");
}
