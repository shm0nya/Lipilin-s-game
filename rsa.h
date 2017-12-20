#ifndef RSA_H
#define RSA_H

#include <QDialog>

namespace Ui {
class rsa;
}

class rsa : public QDialog
{
    Q_OBJECT

public:
    explicit rsa(QWidget *parent = 0);
    ~rsa();

private slots:
    void on_button_rsa_key_generate_2_clicked();

    void on_button_crypto_cansel_2_clicked();

    void on_button_send_messege_clicked();

    void on_button_back_clicked();

    void on_button_load_img_2_clicked();

    void on_button_choose_img_2_clicked();

private:
    Ui::rsa *ui;
};

#endif // RSA_H
