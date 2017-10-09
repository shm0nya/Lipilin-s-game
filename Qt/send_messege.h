#ifndef SEND_MESSEGE_H
#define SEND_MESSEGE_H

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QImage>
#include <vector>

#include <fun.h>


namespace Ui {
class send_messege;
}

class send_messege : public QDialog
{
    Q_OBJECT

public:
    explicit send_messege(QWidget *parent = 0);
    ~send_messege();

private slots:

    void on_button_load_img_clicked();

    void on_button_p_key_generate_clicked();

    void on_button_s_key_generate_clicked();

    void on_button_save_img_clicked();

    void on_button_crypto_p_clicked();

    void on_button_crypto_s_clicked();

    void on_button_algoritm_crypto_clicked();

    void on_button_paint_clicked();

    void on_button_crypto_cansel_clicked();

    void on_button_algoritm_crypto_delete_clicked();

private:
    Ui::send_messege *ui;
    std::vector<int> p_key;
    std::vector<vector<int>> s_key;
    QImage Loaded_image;
    QImage Encrypted_image;
    bool flag_new_image; /* В случае, когда пользователь состпаил алгоритм, загрузил изображение и жмет на кнопку P или S,
                                необходимо сбросить кнопку, дабы алгоритм не рос постоянно
                         */
    int algoritme_size = 30;
};

QImage encrypt_image_p(QImage encrypted_image, std::vector<int> pb_key); /*
                                                                           Принимает QImage - изображение, которое надо шифровать,
                                                                                     pb_key - ключ блока перестановки
                                                                           Возвращает зашифрованный QImage
                                                                           Алгоритм:
                                                                                 * Каждый пиксель задается своими координтами: высота и ширина.
                                                                                 * Используется цикл со счетчиком count от нуля до Высота*Ширина изображения.
                                                                                 * QImage.pixel(wid,hei)=Qmage.pixel(целая часть от деления count на ширину,
                                                                                 *                                      остаток от деления count на ширину)
                                                                                 *
                                                                                 * Считывается блок пикселей размером с длину блока, заданную пользователем,
                                                                                 * перемешивается, после чего записывается обратно в изображение.
                                                                           */
QImage encrypt_image_s(QImage encrypted_image, std::vector<vector<int>> pb_key);
                                                                            /*
                                                                           Принимает QImage - изображение, которое надо шифровать,
                                                                                     pb_key - ключ блока перестановки
                                                                           Возвращает зашифрованный QImage
                                                                           Алгоритм аналогичен "encrypt_image_p"
                                                                           */

#endif // SEND_MESSEGE_H
