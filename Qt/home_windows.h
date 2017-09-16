#ifndef HOME_WINDOWS_H
#define HOME_WINDOWS_H

#include <QWidget>
#include <QObject>
#include <QUdpSocket>

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
    // Кнопки
    //void Test();


    void ready();

private:
    Ui::Home_windows *ui;
    QString login_name; // логин
    QString level = "1"; // уровень

    QUdpSocket *soket; //сокет
    QMap<QString,QString> UserList;

};

#endif // HOME_WINDOWS_H
