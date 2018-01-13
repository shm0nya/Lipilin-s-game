#ifndef ASIMETRY_H
#define ASIMETRY_H

#include <QDialog>
#include <QTimer>
#include <QString>
#include <QMessageBox>

#include<vector>

#include "fun.h"

namespace Ui {
class asimetry;
}

class asimetry : public QDialog
{
    Q_OBJECT

public:
    explicit asimetry(QWidget *parent = 0);
    ~asimetry();

private slots:
    void on_button_generate_clicked();          // Генерация ключей

    void on_button_exchange_clicked();          // Обмен ключами

    void on_button_back_clicked();

signals:
    void from_rsa_to_home_wnd();                // Сигнал, чтобы вернуться в home_wnd
    void keys_was_generated(int, int, int);     // Сигнал, оповещающий о том, что ключи были сгенерированы



private:
    Ui::asimetry *ui;
    bool flag_key_generated = false;            // Флаг, определяющийЮ были сгенерированы ключи или нет
    int mc = 50;                                // Время, в течение которого идет обмен
    int n, e, d;                      // Ключи RSA
};

#endif // ASIMETRY_H
