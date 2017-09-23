#ifndef HOME_WINDOWS_H
#define HOME_WINDOWS_H

#include <QWidget>
#include <QObject>
#include <QList>
#include <QUdpSocket>
#include <QMessageBox>
//-------- Работа с изображениями-------//
#include <QPixmap>

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

private slots:

    void on_button_send_messege_clicked();

private:
    Ui::Home_windows *ui;
    QString login_name; // логин
    QString level = "1"; // уровень
    QString key; // ключ
    QString iOverhear; // кого пользователь прослушивает
    QList <QString> meOverhear; // кто пользователя прослушивает
    QUdpSocket *soket; //сокет
    QMap<QString,QString> UserList;
    /*----------------------------------------------*/
    send_messege send_messege_window;

};


#endif // HOME_WINDOWS_H
