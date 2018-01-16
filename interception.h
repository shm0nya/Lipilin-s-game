#ifndef INTERCEPTION_H
#define INTERCEPTION_H

#include <QDialog>
#include <vector>
#include <QGridLayout>
#include <QMessageBox>

#include "qpb_modify.h"

struct inter_messege
{
    QImage img;             // Зашифрованное изображение
    QImage original_image;  // Оригинальное изображение
    QString p_key;
    int p_key_size;
    QString s_key;
    int s_key_size;
    int i;
    int j;
    QString algoritm;
    QString code;
};

namespace Ui {
class interception;
}

class interception : public QDialog
{
    Q_OBJECT

signals:
    void homecomig(); // Угадайте пасхалку
    void show_info_at_messege(int); // Посылает сам себе, при нажатии на кнопку
    void go_to_crypto(QImage img, QString code, int i, int j);

private slots:
    void show_info_at_messege_on_index(int i);

public:
    explicit interception(QWidget *parent = 0);
    ~interception();
    void add_new_messege(QImage img, QImage orig_image,
                         QString p_key, int p_key_size,
                         QString s_key, int s_key_size,
                         int i, int j, QString algoritm, QString code);

    QString get_login_of_intercept(){return login_of_intercept;}
    void set_login_of_intercept(QString login){login_of_intercept = login;}
    void set_rsa_info(QImage img, QString code);
    void up_level(int level);
    void clearLayout( QLayout* layout );

private slots:
    void on_button_back_clicked();  // Возврат в окно home_windows

    void on_button_to_send_messege_clicked();

    void on_button_decrypt_clicked();

private:
    Ui::interception *ui;
    std::vector<QPB_modify*> buttons_of_messege;
    std::vector<inter_messege> intercepted_messeges;
    QGridLayout *lay;
    QString login_of_intercept;
    bool flag_now_using_message = false;
    bool flag_decr = false;
    int index_message;                                  // Какое сейчас используется перехваченное сообщение
};

#endif // INTERCEPTION_H
