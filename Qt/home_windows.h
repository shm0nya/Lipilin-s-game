#ifndef HOME_WINDOWS_H
#define HOME_WINDOWS_H

#include <QWidget>
#include <QObject>
#include <QList>
#include <QUdpSocket>
#include <QMessageBox>
//-------- Работа с изображениями-------//
#include <QImage>

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

    void on_Button_load_origin_img_clicked();

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
    QString img_original_puth;
};


#endif // HOME_WINDOWS_H
