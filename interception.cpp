#include "interception.h"
#include "ui_interception.h"

interception::interception(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interception)
{
    ui->setupUi(this);
    lay = new QGridLayout;
    ui->scroll_inercept_content->setLayout(lay);

    connect(this, SIGNAL(show_info_at_messege(int)), this, SLOT(show_info_at_messege_on_index(int)) );

    int level = 1;
    ui->button_decrypt->setEnabled(level>=4);
}

interception::~interception()
{
    delete ui;
}

void interception::on_button_back_clicked()
{
    emit this->homecomig();
}

void interception::add_new_messege(QImage img, QImage orig_image,
                                   QString p_key, int p_key_size,
                                   QString s_key, int s_key_size,
                                   int i, int j, QString algoritm, QString code)
{
    inter_messege msg;
    msg.img = img;
    msg.original_image = orig_image;
    msg.p_key = p_key;
    msg.p_key_size = p_key_size;
    msg.s_key = s_key;
    msg.s_key_size = s_key_size;
    msg.i = i;
    msg.j = j;
    msg.algoritm = algoritm;
    msg.code = code;
    intercepted_messeges.push_back(msg);

    QPB_modify *pb = new QPB_modify;
    pb->i = intercepted_messeges.size() - 1;
    pb->setText("Msg from " + login_of_intercept + " №" + QString::number(pb->i));
    connect(pb, &QPushButton::clicked, [this, pb](){
        emit this->show_info_at_messege(pb->i);
    });

    lay->addWidget(pb, pb->i, 0);
}

void interception::show_info_at_messege_on_index(int i)
{
    inter_messege msg = intercepted_messeges[i];
    index_message = i;
    flag_now_using_message = true;

    ui->image_intercept->setPixmap(QPixmap::fromImage(msg.img).scaled(ui->image_intercept->size()));
    ui->lbl_algoritm_value->setText(msg.algoritm);
    ui->lbl_s_size_value->setText(QString::number(msg.s_key_size));
    ui->lbl_p_size_value->setText(QString::number(msg.p_key_size));
    ui->lbl_s_key_vlaue->setText(msg.s_key);
    ui->lbl_p_key_value->setText(msg.p_key);
    ui->lbl__i_value->setText(QString::number(msg.i));
    ui->lbl_j_value->setText(QString::number(msg.j));

    ui->image_intercept_dec->setPixmap(QPixmap::fromImage(QImage(":/images/question.png")));

    if (msg.algoritm == "RSA")
    {
        QMessageBox::information(this, "omg", "Этот игрок зашифровал сообщение с помощью алгоритма RSA, расшифровать не получится"
                                              "Не самый умный ход с его стороны, не такли?");
    }

    flag_decr = false;
}

void interception::on_button_to_send_messege_clicked()
{
    if (flag_now_using_message == false)
    {
        QMessageBox::information(this, "error", "Не выбрано сообщение");
        return;
    }

    if (flag_decr == false)
    {
        QMessageBox::information(this, "error", "Сообщение не расшифровано");
        return;
    }


    emit this->go_to_crypto(intercepted_messeges[index_message].original_image,
                            intercepted_messeges[index_message].code,
                            intercepted_messeges[index_message].i,
                            intercepted_messeges[index_message].j);
}

void interception::set_rsa_info(QImage img, QString code)
{
    inter_messege msg;
    msg.img = img;
    msg.p_key = "none";
    msg.p_key_size = 0;
    msg.s_key = "none";
    msg.s_key_size = 0;
    msg.i = 0;
    msg.j = 0;
    msg.algoritm = "RSA";
    msg.code = code;
    intercepted_messeges.push_back(msg);

    QPB_modify *pb = new QPB_modify;
    pb->i = intercepted_messeges.size() - 1;
    pb->setText("Msg from " + login_of_intercept + " №" + QString::number(pb->i));
    connect(pb, &QPushButton::clicked, [this, pb](){
        emit this->show_info_at_messege(pb->i);
    });

    lay->addWidget(pb, pb->i, 0);
}

void interception::on_button_decrypt_clicked()
{
    if (flag_now_using_message == false)
    {
        QMessageBox::information(this, "error", "Не выбрано перехваченное сообщение");
        return;
    }

    inter_messege msg = intercepted_messeges[index_message];
    if ((msg.algoritm == "RSA") || (msg.p_key == "unknown"))
    {
        QMessageBox::information(this, "error", "Не получилось расшифровать."
                                                 "Возможно применялась ассиметричная криптография для"
                                                 "передачи ключей или шифрования."
                                                 "Но вы можете попробовать угадать, какое это изображение.");
        return;
    }

    int wid = ui->image_intercept_dec->width();
    int hei = ui->image_intercept_dec->height();
    ui->image_intercept_dec->setPixmap(QPixmap::fromImage(msg.original_image).scaled(wid, hei));

    flag_decr = true;
}

void interception::up_level(int level)
{
    ui->button_decrypt->setEnabled(level>=4);
}
