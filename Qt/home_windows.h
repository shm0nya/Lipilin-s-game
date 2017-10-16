#ifndef HOME_WINDOWS_H
#define HOME_WINDOWS_H

#include <QWidget>
#include <QObject>
#include <QList>
#include <QUdpSocket>
#include <QString>

#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
//-------- Работа с изображениями-------//
#include <QPixmap>
#include <QImage>

#include <vector>

#include <fun.h>
#include <send_messege.h>

namespace Ui {
class Home_windows;
}

class Home_windows : public QWidget
{
    Q_OBJECT

public:
    explicit Home_windows(QString str_login, QWidget *parent = 0);
    ~Home_windows();
    QMap<QString,QString> config();
    void StatusOnline();
    QString takeLogin() const { return login_name; }
    void create_img_buttons(vector<vector<QImage>> &cut, int n, int m);

private slots:

    void on_button_send_messege_clicked();

    void ready();

private:
    Ui::Home_windows *ui;
    QString login_name; // логин
    QString level;
    QString iOverhear; // кого пользователь прослушивает
    QList <QString> meOverhear; // кто пользователя прослушивает
    QUdpSocket *soket; //сокет
    QMap<QString,QString> UserList;
    /*----------------------------------------------*/
    send_messege send_messege_window;

    /* Deafult values */
};

vector <vector<QImage>> cut_image(QImage &image, int n, int m); /*Функция, которая разрезает изображение на n*m кусков
                                                    #! Функция универсальная, но предполагается, что изображение 500*500
                                                    Принимает Изображение, n,m
                                                    Возвращает массив размера n*m с изображениями
                                                    */



#endif // HOME_WINDOWS_H
