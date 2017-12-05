#include "send_messege.h"
#include "ui_send_messege.h"

#include <QLayout>
#include <QLabel>

send_messege::send_messege(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::send_messege)
{
    ui->setupUi(this);

    Loaded_image.load(":/images/test.png");
    Encrypted_image = Loaded_image;
    int wid = ui->img_original->width();
    int hei = ui->img_original->height();
    ui->img_original->setPixmap(QPixmap::fromImage(Loaded_image.scaled(wid,hei)));
    ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image.scaled(wid,hei)));


    ui->lbl_algoritm_value->setText("");
    ui->button_crypto_p->setEnabled(!p_key.empty());
    ui->button_crypto_s->setEnabled(!s_key.empty());

    QRegExp is_value_variable("[a-zA-Z0-9а-яА-Я]{1,20}");
    ui->p_key_edit->setValidator(new QRegExpValidator(is_value_variable, this));
    ui->s_key_edit->setValidator(new QRegExpValidator(is_value_variable, this));

    QRegExp is_coordinate_variable("[0-9]{0,5}");
    ui->edit_coordinate_i->setValidator((new QRegExpValidator(is_coordinate_variable, this)));
    ui->edit_coordinate_j->setValidator((new QRegExpValidator(is_coordinate_variable, this)));

    connect(ui->button_choose_img, SIGNAL(clicked()), this, SIGNAL(show_ch_buttons_sign()));
    connect(ui->button_make_img, SIGNAL(clicked()), this, SIGNAL(show_make_img_wnd()));
}

send_messege::~send_messege()
{
    delete ui;
}

void send_messege::on_button_load_img_clicked()
{
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

void send_messege::on_button_p_key_generate_clicked()
{
    /* Проверка как при нажатии на S
     * В случае не выполнения данных условий - выводи окно ошибки и завершается метод
     * В случае успеха - выводит данные пользователю:label show_now_use...
     * Затем генерирует ключ перестановок, записывает его в атрибут p_key
     * Делает активной клавишу "зашифровать P" */


    /* Проверка на "шифрование различными ключами" */
    if ((Loaded_image != Encrypted_image) && (!p_key.empty()))
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"warning",
                              "Вы меняете ключ, при уже зашифрованной картинке "
                              "это приведет к тому, что изображение вернется в начальное состояние. "
                              "Вы уверены в своем решении?",
                              QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            Encrypted_image = Loaded_image;
            int lblwid = ui->img_changed->width();
            int lblhei = ui->img_changed->height();
            ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image).scaled(lblwid,lblhei));
            flag_new_image = true;
        }
        else
            return;
    }

    /* Проверка на "задан ли верно ключ" */
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

    /* Инициирование стартового значения генератора */
    string value_key = ui->p_key_edit->text().toStdString();
    int generator_start = 0;
    for (int i = 0; i < int(value_key.size()); i++)
        generator_start = generator_start + value_key[i];


    p_key = pblok_key(ui->p_key_size_edit_spbox->value(), generator_start);
    ui->button_crypto_p->setEnabled(true);

    QString str = QString("%1").arg(ui->p_key_size_edit_spbox->value());// Перевод int в строку
    ui->lbl_p_key_size->setText(str);
    ui->lbl_p_key_value->setText(ui->p_key_edit->text());
}

void send_messege::on_button_s_key_generate_clicked()
{
    /* При нажатии проверяет: 1) задано ли генерирующее слово
     *                        2) Длина = 0 или нет
     *
     * В случае не выполнения данных условий - выводи окно ошибки и завершается метод
     * Проверяет следующую ситуацию: сообщение уже зашифровано, пользователь пытается шифровать на другом ключе
#!   * #!!! Реализован Виженер, а не SBLOK
     * В случае успеха - выводит данные пользователю:label show_now_use...
     * Затем генерирует ключ перестановок, записывает его в атрибут p_key
     * Делает активной клавишу "Зашифровать S"  */

    /* Проверка на "шифрование различными ключами" */
    if ((Loaded_image != Encrypted_image) && (!s_key.empty()))
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"warning",
                              "Вы меняете ключ, при уже зашифрованной картинке "
                              "это приведет к тому, что изображение вернется в начальное состояние. "
                              "Вы уверены в своем решении?",
                              QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            Encrypted_image = Loaded_image;
            int lblwid = ui->img_changed->width();
            int lblhei = ui->img_changed->height();
            ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image).scaled(lblwid,lblhei));
            flag_new_image = true;
        }
        else
            return;
    }

    /* Проверка на "задан ли верно ключ" */
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

    /* Инициирование стартового значения генератора */
    string value_key = ui->s_key_edit->text().toStdString();
    int generator_start = 0;
    for (int i = 0; i < int(value_key.size()); i++)
        generator_start = generator_start + value_key[i];


    s_key = sblok_like_vigener_key(ui->s_key_size_edit_spbox->value(), generator_start);
    ui->button_crypto_s->setEnabled(true);

    QString str = QString("%1").arg(ui->s_key_size_edit_spbox->value());// Перевод int в строку
    ui->lbl_s_key_size->setText(str);
    ui->lbl_s_key_value->setText(ui->s_key_edit->text());
}

void send_messege::on_button_crypto_p_clicked()
{
    /* Проверки как при нажатии S
     * Проверка, на безграничность роста алгоритма
     * Шифрование
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
    /* Работает аналоично шифрованию P */
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
    /* Считывает строку и шифрует, в зависимости от символа */

    if (ui->lbl_algoritm_value->text()=="")
    {
        QMessageBox::information(this,"good_luck","Вы пытаетесь зашифровать без алгоритма");
        return;
    }

    flag_new_image = false;
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
    if( flag_new_image == true)
    {
        QMessageBox::information(this, "error", "Вы не применили ни один шифр");
        return;
    }

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
    if (Encrypted_image != Loaded_image)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"warning",
                              "Вы меняете алгоритм, при уже зашифрованной картинке "
                              "это приведет к тому, что изображение вернется в начальное состояние. "
                              "Вы уверены в своем решении?",
                              QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            Encrypted_image = Loaded_image;
            int lblwid = ui->img_changed->width();
            int lblhei = ui->img_changed->height();
            ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image).scaled(lblwid,lblhei));
            flag_new_image = true;
        }
        else
            return;
    }

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
        
        // Шифрование и запись зашифрованных пикселей
        if (int(temp.size())==p_size)
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
    // Существует out of range of image Хз как фиксить
    int wid = encrypted_image.width();
    int hei = encrypted_image.height();
    int blok_size = sb_key[0].size() * 3;

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
        if (int(temp.size())==blok_size)
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
    int blok_size = sb_key[0].size()*3;

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

        // Шифроание и за,пись зашифрованных пикселей
        if (int(temp.size())==blok_size)
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

void send_messege::user_choose_img(QImage img, QString code)
{
    Loaded_image= img;
    flag_new_image = true;
    Encrypted_image = Loaded_image;
    now_using_rune_code = code;

    int wid = ui->img_original->width();
    int hei = ui->img_original->height();
    ui->img_original->setPixmap(QPixmap::fromImage(Loaded_image.scaled(wid,hei)));

    int widch = ui->img_changed->width();
    int heich = ui->img_changed->height();
    ui->img_changed->setPixmap(QPixmap::fromImage(Encrypted_image.scaled(widch,heich)));
}

void send_messege::set_position_of_img(int i, int j)
{
    ui->edit_coordinate_i->setText(QString::number(i+1)); // +1, чтобы пользователю было удобнее считать
    ui->edit_coordinate_j->setText(QString::number(j+1));
}

void send_messege::on_button_send_messege_clicked()
{
    QString code = now_using_rune_code;

    int i;
    QString i_str = ui->edit_coordinate_i->text();
    if (i_str == "")
        i = -1;
    else
        i = ui->edit_coordinate_i->text().toInt();

    int j;
    QString j_str = ui->edit_coordinate_j->text();
    if (j_str == "")
        j = -1;
    else
        j = ui->edit_coordinate_j->text().toInt();

    QString p_key_str = ui->lbl_p_key_value->text();

    int p_key_size;
    QString p_key_size_str = ui->lbl_p_key_size->text();
    if (p_key_size_str == "none")
        p_key_size = 0;
    else
        p_key_size = p_key_size_str.toInt();

    QString s_key_str = ui->lbl_s_key_value->text();


    int s_key_size;
    QString s_key_size_str = ui->lbl_s_key_size->text();
    if (s_key_size_str == "none")
        s_key_size = 0;
    else
        s_key_size = s_key_size_str.toInt();

    QString algoritm = ui->lbl_algoritm_value->text();

    emit this->player_send_messege(code, p_key_str, p_key_size, s_key_str, s_key_size, i, j, algoritm);
}

void send_messege::players_img_verdict(bool verdict)
{
    if (verdict == false)
        QMessageBox::information(this, "Марио, твоя принцесса в другом замке", "Это неверное изображение");
    else
    {
        QMessageBox::information(this, "Nice", "Это верное изображение");
        /* Здесь код, который запускает функцию, говорящую, что все хорошо*/
    }
}

void send_messege::on_button_back_clicked()
{
   emit this->change_wnd_to_homewnd();
}

void send_messege::set_intercept_info(QImage img,
                        QString p_key, int p_key_size,
                        QString s_key, int s_key_size,
                        int i, int j, QString algoritm)
{
    this->user_choose_img(img, "");
    flag_new_image = false;

    ui->p_key_edit->setText(p_key);
    ui->s_key_edit->setText(s_key);
    ui->p_key_size_edit_slider->setValue(p_key_size);
    ui->s_key_size_edit_slider->setValue(s_key_size);
    ui->lbl_algoritm_value->setText(algoritm);

    this->set_position_of_img(i+1, j+1);
}

void send_messege::on_button_swap_clicked()
{
    int lblwid = ui->img_changed->width();
    int lblhei = ui->img_changed->height();

    ui->img_changed->setPixmap(QPixmap::fromImage(Loaded_image).scaled(lblwid,lblhei));

    int lblwid2 = ui->img_original->width();
    int lblhei2 = ui->img_original->height();

    ui->img_original->setPixmap(QPixmap::fromImage(Encrypted_image).scaled(lblwid2,lblhei2));

    // А в питоне так можно!!! Loaded_image, Encrypted_image = Encrypted_image, Loaded_image;
    QImage temp = Loaded_image;
    Loaded_image = Encrypted_image;
    Encrypted_image = temp;
}

QImage send_messege::encrypt_img_to_intercept(QImage img, QString pkey, int pkey_size,
                                            QString skey, int skey_size, QString algoritm)
{
    int generator_start = 0;
    for (int i = 0; i < int(pkey.size()); i++)
    {
        generator_start = generator_start + pkey[i].toLatin1();
    }
    vector<int> pbk = pblok_key(pkey_size, generator_start);

    generator_start = 0;
    for (int i = 0; i < int(skey.size()); i++)
    {
        generator_start = generator_start + skey[i].toLatin1();
    }
    vector<vector<int>> sbk = sblok_like_vigener_key(skey_size, generator_start);

    for (int i = 0; i<algoritm.size(); i++)
    {
        if(algoritm[i]=='P')
            img = encrypt_image_p(img, pbk);
        else
            img = encrypt_image_s(img, sbk);
    }

    return img;
}
