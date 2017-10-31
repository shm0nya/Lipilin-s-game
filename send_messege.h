/* Mode = player
 * Данное окно предназначено для шифрования и отправки пользователем изображения
 * Окно позволяет шифровать P, S, PS, (PS)*n и многое другое
*/

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
    void user_choose_img(QImage img, int i, int j); /* Выбранное пользователем изображение с его координатами устанавливается как активное */
    ~send_messege();

signals:
                    // Все сигналы ловит mainwindow //
    void change_wnd_to_homewnd(); /* Сигнал для смены окна на homewindow */
    void show_ch_buttons_sign(); /* Сигнал для показа окна choose_img */
    void show_make_img_wnd();/* Сигнал для показа окна make img*/

private slots:
    void on_button_load_img_clicked(); /* Позволяет пользователю загрузить своё изображение (подробнее см в send_messege.cpp) */
    void on_button_p_key_generate_clicked();/* Генерирует ключ P (подробнее см в send_messege.cpp) */
    void on_button_s_key_generate_clicked();/* Генерирует ключ S (подробнее см в send_messege.cpp) */
    void on_button_crypto_p_clicked();/* Шифрует P (подробнее см в send_messege.cpp) */
    void on_button_crypto_s_clicked();/* Шифрует S (подробнее см в send_messege.cpp) */
    void on_button_algoritm_crypto_clicked();/* Шифрует по алгоритму (подробнее см в send_messege.cpp) */
    void on_button_crypto_cansel_clicked();/* Расшифровывает последний шифр (подробнее см в send_messege.cpp) */
    void on_button_algoritm_crypto_delete_clicked(); /* Сбрасыывает алгоритм (подробнее см в send_messege.cpp) */

private:
    Ui::send_messege *ui;
    std::vector<int> p_key;
    std::vector<vector<int>> s_key;
    QImage Loaded_image;                    // Загруженное изображение
    QImage Encrypted_image;                 // Зашифрованное изображение
    bool flag_new_image;                    /* В случае, когда пользователь составил алгоритм, загрузил изображение и жмет на кнопку P или S,
                                             * необходимо сбросить кнопку, дабы алгоритм не рос постоянно */
    int algoritme_size = 30;                // Максимльная длина алгоритма
};

QImage encrypt_image_p(QImage encrypted_image, std::vector<int> pb_key); /* Принимает QImage - изображение, которое надо шифровать,
                                                                          *           pb_key - ключ блока перестановки
                                                                          * Возвращает зашифрованный QImage
                                                                          * Алгоритм:
                                                                          *            Каждый пиксель задается своими координтами: высота и ширина.
                                                                          *            Используется цикл со счетчиком count от нуля до Высота*Ширина изображения.
                                                                          *            QImage.pixel(wid,hei)=Qmage.pixel(целая часть от деления count на ширину,
                                                                          *                                      остаток от деления count на ширину)
                                                                          *
                                                                          *            Считывается блок пикселей размером с длину блока, заданную пользователем,
                                                                          *            перемешивается, после чего записывается обратно в изображение.
                                                                          */

QImage encrypt_image_s(QImage encrypted_image, std::vector<vector<int>> sb_key);
                                                                            /* Принимает QImage - изображение, которое надо шифровать,
                                                                             *           pb_key - ключ блока перестановки
                                                                             * Возвращает зашифрованный QImage
                                                                             * Алгоритм аналогичен "encrypt_image_p"
*/
QImage decrypt_image_s(QImage encrypted_image, std::vector<vector<int>> sb_key); /* Делает то же, что и encrypt, только использует sblok_like_vigener_revers*/

#endif // SEND_MESSEGE_H
