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
#include <QEventLoop>
#include <QTimer>

#include <vector>

#include "fun.h"


namespace Ui {
class send_messege;
}

class send_messege : public QDialog
{
    Q_OBJECT

public:
    explicit send_messege(QWidget *parent = 0);

    void user_choose_img(QImage img, QString code);       /* Выбранное пользователем изображение с его координатами устанавливается как активное */
    void user_made_img(QImage img, QString code);
    void set_position_of_img(int i, int j); // Установка позици изображения (в choose_button используется через mainwindow)
    void players_img_verdict(bool verdict); // Проверка правильности изображения

    void set_intercept_info(QImage img,
                            QString p_key, int p_key_size,
                            QString s_key, int s_key_size,
                            int i, int j, QString algoritm, QString code);

    QImage encrypt_img_to_intercept(QImage img, QString pkey_str, int pkey_size,
                                                QString skey_str, int skey_size,
                                                QString algoritm);

    ~send_messege();

signals:
    void change_wnd_to_homewnd(); /* Сигнал для смены окна на homewindow */
    void show_ch_buttons_sign();  /* Сигнал для показа окна choose_img */
    void show_make_img_wnd();     /* Сигнал для показа окна make img*/

    void player_send_messege(QString,QString,int,QString,int,int,int,QString);/* Передает в mainwindow следующие данные:
                                                                                     * 1) Qimage Изображение исходное и зашифрованное
                                                                                     * 2) QString P_key, int длина ключа P
                                                                                     * 3) QString s_key, int длина ключа S
                                                                                     * 4) int i, int j координаты в сетке
                                                                                     * 5) Алгоритм
                                                                                     *
                                                                                     * в mainwindow сравнивается с исходным.
                                                                                     * Если нас прослушивают отправляет тому, кто прослушивает
                                                                                     */


private slots:
    void on_button_load_img_clicked(); /* Позволяет пользователю загрузить своё изображение (подробнее см в send_messege.cpp) */
    void on_button_p_key_generate_clicked();/* Генерирует ключ P (подробнее см в send_messege.cpp) */
    void on_button_s_key_generate_clicked();/* Генерирует ключ S (подробнее см в send_messege.cpp) */
    void on_button_crypto_p_clicked();/* Шифрует P (подробнее см в send_messege.cpp) */
    void on_button_crypto_s_clicked();/* Шифрует S (подробнее см в send_messege.cpp) */
    void on_button_algoritm_crypto_clicked();/* Шифрует по алгоритму (подробнее см в send_messege.cpp) */
    void on_button_crypto_cansel_clicked();/* Расшифровывает последний шифр (подробнее см в send_messege.cpp) */
    void on_button_algoritm_crypto_delete_clicked(); /* Сбрасыывает алгоритм (подробнее см в send_messege.cpp) */
    void on_button_send_messege_clicked();
    void on_button_back_clicked();

private:
    Ui::send_messege *ui;
    std::vector<int> p_key;                 // Ключ Р
    std::vector<int> p_key_intercepted;
    std::vector<vector<int>> s_key;         // Ключ S
    std::vector<vector<int>> s_key_intercepted;
    QImage Loaded_image;                    // Загруженное изображение
    QImage Encrypted_image;                 // Зашифрованное изображение
    QImage Intercepted_image;
    bool flag_new_image;                    /* В случае, когда пользователь составил алгоритм, загрузил изображение и жмет на кнопку P или S,
                                             * необходимо сбросить кнопку, дабы алгоритм не рос постоянно */
    int algoritme_size = 30;                // Максимльная длина алгоритма
    QString now_using_rune_code = "";
    int mc;
    bool flag_p_key_ex = false;             // Флаг, определяющий существет ли ключ (при перехвате сообщений)
    bool flag_s_key_ex = true;
    bool flag_img_intercept;
    QString temoalgor;
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
