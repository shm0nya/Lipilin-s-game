#ifndef HOME_WINDOWS_H
#define HOME_WINDOWS_H

#include <QWidget>
#include <QObject>
#include <QList>
#include <QUdpSocket>
#include <QMessageBox>

#include <fun.h>

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


   // void ready();


    void on_friend_edit_editingFinished();

    void on_opponent_edit_editingFinished();

    void on_P_key_size_slider_valueChanged(int value);

    void on_S_key_size_slider_valueChanged(int value);

    void on_P_key_generate_button_clicked();

    void on_S_key_generate_button_clicked();

signals:
    void mistake (QString str);


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
    std::vector<int> p_key;
    std::vector<int> s_key;
};


class error: public QObject
{
    // Простой класс для вывод ошибок. Код ошибки - на будущее, мб
    Q_OBJECT
private:
    int code;
public slots:

    void send_error(QString str)
    {
        /*
         * Принимает один параметра - строку ошибки.
         * Выводит на экран данные об этой ошибке
        */
        QMessageBox msg;
        msg.setText(str);
        msg.exec();
    }
};


#endif // HOME_WINDOWS_H
