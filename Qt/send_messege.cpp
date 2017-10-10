#include "send_messege.h"
#include "ui_send_messege.h"

send_messege::send_messege(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::send_messege)
{
    ui->setupUi(this);
    ui->lbl_algoritm_value->setText("");
    ui->button_crypto_p->setEnabled(!p_key.empty());
    ui->button_crypto_s->setEnabled(!s_key.empty());
}

send_messege::~send_messege()
{
    delete ui;
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
         * После загрузки устанавливаюстя два изображения - оригинальное и "изменяемое"
         *
         * Переменные wid и hei обозначают соответственно ширину и высоту
         * Введены для большей понятности кода
        */

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

void send_messege::on_button_crypto_p_clicked()
{
    /*
     * Сначал идет проверка, загружено ли изображение.
     * Если нет - выдается сообщение об ошибке.
     *
     * Проверка, на безграничность роста алгоритма
     *
     * Шифрование
     *
     * После обработки добавляет букву "P" в алгоритм
     * Устанавливает зашифрованную картинку на экран
    */

    if(Loaded_image.isNull())
    {
        QMessageBox::information(this,"Error","Вы не загрузили изображение.");
        return;
    }

    if (flag_new_image == true)
    {
        flag_new_image = false;
        ui->lbl_algoritm_value->setText("");
    }

    QString algoritm = ui->lbl_algoritm_value->text();
    if (algoritm.size() > algoritme_size)
    {
        QMessageBox::information(this,"Error","Слишком большой алгоритм");
        return;
    }
    algoritm += "P";
    ui->lbl_algoritm_value->setText(algoritm);

    Encrypted_image = encrypt_image_p(Encrypted_image, p_key);

    int lblwid = ui->img_changed->width();
    int lblhei = ui->img_changed->height();

    ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image).scaled(lblwid,lblhei));
}

void send_messege::on_button_crypto_s_clicked()
{
    /*
     * Работает аналоично шифрованию P
    */
    if(Loaded_image.isNull())
    {
        QMessageBox::information(this,"Error","Вы не загрузили изображение.");
         return;
    }

    if (flag_new_image == true)
    {
        flag_new_image = false;
        ui->lbl_algoritm_value->setText("");
    }

    Encrypted_image = encrypt_image_s(Encrypted_image, s_key);

    QString algoritm = ui->lbl_algoritm_value->text();
    if (algoritm.size() > algoritme_size)
    {
        QMessageBox::information(this,"Error","Слишком большой алгоритм");
        return;
    }
    algoritm += "S";
    ui->lbl_algoritm_value->setText(algoritm);


    int lblwid = ui->img_changed->width();
    int lblhei = ui->img_changed->height();

    ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image).scaled(lblwid,lblhei));
}

void send_messege::on_button_algoritm_crypto_clicked()
{
    /*
     Считывает строку и шифрует, в зависимости от символа
    */
    if (ui->lbl_algoritm_value->text()=="")
    {
        QMessageBox::information(this,"good_luck","Вы пытаетесь зашифровать без алгоритма");
        return;
    }

    Encrypted_image = Loaded_image;
    QString algoritme = ui->lbl_algoritm_value->text();
    for (int i = 0; i<algoritme.size(); i++)
    {
        if(algoritme[i]=='P')
            Encrypted_image = encrypt_image_p(Encrypted_image, p_key);
        else
            Encrypted_image = encrypt_image_s(Encrypted_image, s_key);
    }
    int lblwid = ui->img_changed->width();
    int lblhei = ui->img_changed->height();

    ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image).scaled(lblwid,lblhei));
}

void send_messege::on_button_crypto_cansel_clicked()
{
    QString algoritme = ui->lbl_algoritm_value->text();
    if (algoritme == "")
    {
        QMessageBox::information(this,"Oops","Вы не применили ни один шифр");
        return;
    }

    if (algoritme[algoritme.size()-1] == 'P')
    {
        vector<int> revers = pblok_key_revers(p_key);
        Encrypted_image = encrypt_image_p(Encrypted_image, revers);
    }
    else
        Encrypted_image = decrypt_image_s(Encrypted_image, s_key);
    algoritme.chop(1);
    ui->lbl_algoritm_value->setText(algoritme);


    int lblwid = ui->img_changed->width();
    int lblhei = ui->img_changed->height();

    ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image).scaled(lblwid,lblhei));
}

void send_messege::on_button_algoritm_crypto_delete_clicked()
{
    ui->lbl_algoritm_value->setText("");
}

QImage encrypt_image_p(QImage encrypted_image, vector<int> pb_key)
{
    // Инициируются переменные для удобства использования
    int wid = encrypted_image.width();
    int hei = encrypted_image.height();
    int p_size = pb_key.size();

    for (int i = 0; i < hei*wid;)
    {

        // Считывание и шифрование
        vector<QRgb> temp;
        for (int j=0; j<p_size; j++)
        {
            QRgb t;
            t=encrypted_image.pixel(i%wid, i/wid);
            temp.push_back(t);
            i++;
        }

        // Шифроание и запись зашифрованных пикселей
        if (temp.size()==p_size)
        {
            temp = pblok_use(temp, pb_key);
            for (int j = 0; j<p_size;j++)
            {
                int k=i-p_size+j;
                encrypted_image.setPixel(k%wid, k/wid, temp[j]);
            }
        }
    }
    return encrypted_image;
}

QImage encrypt_image_s(QImage encrypted_image, std::vector<vector<int>> sb_key)
{
    int wid = encrypted_image.width();
    int hei = encrypted_image.height();
    int blok_size = sb_key.size();

    // Считывание
    for (int i = 0; i < hei*wid;)
    {
        vector<QRgb> temp;
        for (int j=0; j<blok_size; j++)
        {
            QRgb t;
            t=encrypted_image.pixel(i%wid, i/wid);
            temp.push_back(t);
            i++;
        }

        // Шифроание и запись зашифрованных пикселей
        if (temp.size()==blok_size)
        {
            temp = sblok_like_vigener_use(temp, sb_key);
            for (int j = 0; j<blok_size;j++)
            {
                int k=i-blok_size+j;
                encrypted_image.setPixel(k%wid, k/wid, temp[j]);
            }
        }
    }
    return encrypted_image;
}

QImage decrypt_image_s(QImage encrypted_image, std::vector<vector<int>> sb_key)
{
    int wid = encrypted_image.width();
    int hei = encrypted_image.height();
    int blok_size = sb_key.size();

    // Считывание
    for (int i = 0; i < hei*wid;)
    {
        vector<QRgb> temp;
        for (int j=0; j<blok_size; j++)
        {
            QRgb t;
            t=encrypted_image.pixel(i%wid, i/wid);
            temp.push_back(t);
            i++;
        }

        // Шифроание и запись зашифрованных пикселей
        if (temp.size()==blok_size)
        {
            temp = sblok_like_vigener_reverse(temp, sb_key);
            for (int j = 0; j<blok_size;j++)
            {
                int k=i-blok_size+j;
                encrypted_image.setPixel(k%wid, k/wid, temp[j]);
            }
        }
    }
    return encrypted_image;
}

