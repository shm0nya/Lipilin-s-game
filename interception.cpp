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
}

interception::~interception()
{
    delete ui;
}

void interception::on_button_back_clicked()
{
    emit this->homecomig();
}

void interception::add_new_messege(QImage img,
                                   QString p_key, int p_key_size,
                                   QString s_key, int s_key_size,
                                   int i, int j, QString algoritm)
{
    inter_messege msg;
    msg.img = img;
    msg.p_key = p_key;
    msg.p_key_size = p_key_size;
    msg.s_key = s_key;
    msg.s_key_size = s_key_size;
    msg.i = i;
    msg.j = j;
    msg.algoritm = algoritm;
    intercepted_messeges.push_back(msg);

    QPB_modify *pb = new QPB_modify;
    pb->i = intercepted_messeges.size() - 1;
    pb->setText(login_of_intercept + ' ' + QString::number(pb->i));
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

    ui->s_key_size_edit_slider->setValue(msg.s_key_size);
    ui->p_key_size_edit_slider->setValue(msg.p_key_size);

    ui->s_key_edit->setText(msg.s_key);
    ui->p_key_edit->setText(msg.p_key);

    ui->edit_coordinate_i->setText(QString::number(msg.i));
    ui->edit_coordinate_j->setText(QString::number(msg.j));
}

void interception::on_button_to_send_messege_clicked()
{
    if (flag_now_using_message == false)
    {
        QMessageBox::information(this, "error", "Не выбрано сообщение");
        return;
    }

    emit this->go_to_crypto(
                intercepted_messeges[index_message].img,
                intercepted_messeges[index_message].p_key,
                intercepted_messeges[index_message].p_key_size,
                intercepted_messeges[index_message].s_key,
                intercepted_messeges[index_message].s_key_size,
                intercepted_messeges[index_message].i,
                intercepted_messeges[index_message].j,
                intercepted_messeges[index_message].algoritm);
}
