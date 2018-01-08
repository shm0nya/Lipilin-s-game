#include "asimetry.h"
#include "ui_asimetry.h"

asimetry::asimetry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::asimetry)
{
    ui->setupUi(this);
    init_bd();
    ui->progress_bar_exchange->setVisible(false);
}

asimetry::~asimetry()
{
    delete ui;
}

void asimetry::init_bd()
{
    /* База данных ключей для RSA
     * Столбцы:
     * | p | q | n | f_n | e | d |
     */

    int count = 1;      // Количество ключей
    keys_bd.resize(count);   // Выделение памяти под них

    /* Инициализация */
    keys_bd[0] = {"7", "13", "91", "72", "5", "91"};
}

void asimetry::on_button_generate_clicked()
{
    QTime time;
    qsrand(time.secsTo(QTime::currentTime()));
    int pointer = qrand() % keys_bd.size();

    ui->lbl_p_value->setText(keys_bd[pointer][0]);
    ui->lbl_q_value->setText(keys_bd[pointer][1]);
    ui->lbl_n_value->setText(keys_bd[pointer][2]);
    ui->lbl_f_n_value->setText(keys_bd[pointer][3]);
    ui->lbl_e_value->setText(keys_bd[pointer][4]);
    ui->lbl_d_value->setText(keys_bd[pointer][5]);

    flag_key_generated = true;
}

void asimetry::on_button_exchange_clicked()
{
    if (!flag_key_generated)
    {
        QMessageBox::information(this, "error", "Ключи не сгенерированы");
        return;
    }

    ui->progress_bar_exchange->setVisible(true);

    for (int i = 0; i < 100; i++)
    {
        QEventLoop loop;
        QTimer::singleShot(mc, &loop, SLOT(quit()));
        loop.exec();
        loop.exit();
        ui->progress_bar_exchange->setValue(i+1);
    }

    ui->progress_bar_exchange->setVisible(false);
    ui->lbl_status_value->setText("Ключи получены");

    emit this->keys_was_generated();
}

void asimetry::on_button_back_clicked()
{
    emit this->from_rsa_to_home_wnd();
}
