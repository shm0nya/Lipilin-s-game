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
#include <QMap>

#include <vector>

#include "qpb_modify.h"
#include "send_messege.h"

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
    QMap<QString,QString> config();
    void StatusOnline();
    QString takeLogin() const { return login_name; }

signals:
    void change_wnd_to_swnd(); /* Сигнал для переключения с home_window на send_messege */
    void do_it(int, int); /* Сигнал для создания кнопок в choose_button */
    void i_opend(QImage, int, int); /* Сигнал, который шлет созданная кнопка в home_window в main_window для того, чтобы сообщить о том, что кнопка выбрана пользователем */

private slots:
    void on_pushButton_clicked(); /* Заменяет сигнал Старт от рута */
    void ready();

private:
    Ui::home_window *ui;
    QImage original_img;
    QString login_name; // логин
    QString key; // ключ
    QString level;
    QString iOverhear; // кого пользователь прослушивает
    QList <QString> meOverhear; // кто пользователя прослушивает
    QUdpSocket *soket; //сокет
    QMap<QString,QString> UserList;
};

vector <vector<QImage>> cut_image(QImage &image, int n, int m); /* Функция, которая разрезает исходное изображение на n*m частей.
                                                                 * В будущем не понадобится */


#endif // HOME_WINDOW_H
