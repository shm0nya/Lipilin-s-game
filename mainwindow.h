/*
 * MainWindow является центральной частью программы.
 * Все остальные окна общаются межд у собой путем проброса сигналов через MainWindow
 * Существует два варианта работы MainWindow: для root и для player
 * В начале комментария к любым атрибутам, методам, сигналам и слотам MainWindow
 * указано, к какому режиму относится данный объект
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "home_window.h"
#include "send_messege.h"
#include "choose_button.h"
#include "root_window.h"

extern QString name_login;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void rootwindow(); /* Mode = root;
                        * Функция, формирующая окно root и connect для него */

    void playerwindow();/* Mode = player;
                         * Функция, формирующая окно player и connect для него */

private slots:
    void ok_enabled(); /* Mode = any;
                        * Слот, который проверяет, ввёл ли пользователь верное значение в поле "логин" */

    void on_Login_button_clicked(); /* Mode = any;
                                     * Слот, анализирующий "логин" и выполняющий дальнейшие действия */

    void home_wnd__sendmess_wnd(); /* Mode = player;
                                    * Слот, позволяющий переключиться между окном home_window и send_messege */

    void sendmess_wnd__home_wnd();/* Mode = player;
                                   * Слот, позволяющий переключиться между окном send_messege и home_window */

    void create_pb(int i, int j);/* Mode = player;
                                  * Реагирует на сигнал от home_window::do_it(int, int)
                                  * Слот, который создает в окне choose_button кнопку в соответствующей позиции i, j
                                  * Для кнопки задается connect:
                                  *                             в случае, если кнопка открыта - вызывает сигнал choose_button::i_choose_img(...)
                                  *                             иначе вызывает QMessegeBox с информацией об ошибке
                                  * Вызывает метод choose_button::set_image(QPB_modify *pb, int i, int j), который ставит кнопку в соответствующую позицию */

    void show_ch_wnd();/* Mode = player;
                        * Слот, замораживающий окно send_messege и открывающий окно choose_button */

    void then_opend_img(QImage img, int i, int j); /* Mode = player;
                                                    * Слот срабатывает на сигнал home_window::i_opend(QImage, int, int)
                                                    * Слот, который вызывает метод choose_button::open_button(QImage img, int i, int j)
                                                    * Данный метод создает новую кнопку, устанавливает на неё икноку (reverse), делает кнопку активной */
    void if_close_wnd(); /* Mode = player;
                          * Слот срабатывает при закрытии окна choose_button
                          * Активирует окно send_messege */
    void then_choosen_img(QImage img); /* Mode = player
                                        * Ловит сигнал choose_buttons::i_choose_img(QImage)
                                        * Данный слот устанавливает в send_messege то изображение, которое выбрал пользователь в качестве рабочкго */

private:
    Ui::MainWindow *ui;
    home_window *hWnd;
    send_messege *smWnd;
    choose_button *ch_bWnd;
    root_window *rootWnd;
};

#endif // MAINWINDOW_H
