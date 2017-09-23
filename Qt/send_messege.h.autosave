#ifndef SEND_MESSEGE_H
#define SEND_MESSEGE_H

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QImage>
#include <vector>

#include <fun.h>


namespace Ui {
class send_messege;
}

class send_messege : public QDialog
{
    Q_OBJECT

public:
    explicit send_messege(QWidget *parent = 0);
    ~send_messege();

private slots:

    void on_button_load_img_clicked();

    void on_button_p_key_generate_clicked();

    void on_button_s_key_generate_clicked();

    void on_button_save_img_clicked();

    void on_button_crypto_p_clicked();

    void on_button_crypto_s_clicked();

    void on_button_algoritm_crypto_clicked();

    void on_button_paint_clicked();

    void on_button_crypto_cansel_clicked();

private:
    Ui::send_messege *ui;
    std::vector<int> p_key;
    std::vector<vector<int>> s_key;
    QImage Loaded_image;
    QImage Encrypted_image;
};

#endif // SEND_MESSEGE_H
