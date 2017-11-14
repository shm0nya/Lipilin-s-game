/*
 * Домашнее окно пользователя
 * Mode = player
 * В данном окно пользователь может открывать различыне окна путем посыла сигналов в MainWindow
 * Окна, которые можно открыть: 1) send_messege
 *                              2) ...
*/

#ifndef HOME_WINDOW_H
#define HOME_WINDOW_H

#include <QWidget>
#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QPixmap>
#include <QImage>
#include <QUdpSocket>
#include <QMessageBox>

#include <vector>

#include "qpb_modify.h"
#include "send_messege.h"
#include "fun.h"

using namespace std;

namespace Ui {
class home_window;
}

class home_window : public QWidget
{
    Q_OBJECT

public:
    explicit home_window(QString str_login, QWidget *parent = 0);
    ~home_window();
    void create_img_buttons(vector<vector<QImage>> &cut, int n, int m); /* Функция, которая создает иконки изображений (QpusgButton с натянутым QIcon),
                                                                         * каждая кнопка по клику на неё вызывает сигнал home_window::i_opend(QImage, int, int)
                                                                         * После генерации каждой кнопки шлет сигнал home_window::do_it() в Main_window
                                                                         * для того, чтобы создать идентичную кнопку в окне choose_button
                                                                         */

    void add_new_player(QString new_player_login); // Добавляет нового пользователя в список пользователей (ui->list_users)

signals:
    void change_wnd_to_swnd();          /* Сигнал для переключения с home_window на send_messege */
    void do_it(int, int);               /* Сигнал для создания кнопок в окне choose_button */
    void i_opend(QImage, int, int);     /* Сигнал, который шлет созданная кнопка в home_window в main_window для того, чтобы сообщить о том, что кнопка выбрана пользователем */


private slots:
    void on_pushButton_clicked();       /* Заменяет сигнал Старт от рута */
    void NET_datagramm_analysis();

private:
    Ui::home_window *ui;
    QString login_name;
    QImage original_img;                  // Изображение, которое пользователь в данный момент кодирует или декодирует
    vector<vector<QImage>> source_img;    // Исходные изображения, которые прислыает root
    vector<vector<QString>> code_messege; // Закодированные сообщения в картинке. По индексу совпадают с source_img
    int n, m;                             // Размеры сетки картинок

    QUdpSocket *socket;

    void NET_start_messeges_phase_1(QString messeges); // Фаза 1 анализа данных от root (подробнее см протокол в mainwindow)
    void NET_start_messeges_phase_2(QString data);                        // Фаза 2 анализа данных от root
    void game_must_go_on();                                               // Фаза 3 - игру можно начинать
};

vector <vector<QImage>> cut_image(QImage &image, int n, int m); /* Функция, которая разрезает исходное изображение на n*m частей.
                                                                 * В будущем не понадобится */


#endif // HOME_WINDOW_H
