#include "root_window.h"
#include "ui_root_window.h"

root_window::root_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::root_window)
{
    ui->setupUi(this);

    QRegExp is_int("[0-9]{0,3}");
    ui->edit_n->setValidator(new QRegExpValidator(is_int, this));
    ui->edit_m->setValidator(new QRegExpValidator(is_int, this));
    ui->edit_size_img->setValidator(new QRegExpValidator(is_int, this));

    set_default_messege();
    create_images();
}

root_window::~root_window()
{
    delete ui;
}

void root_window::on_button_apply_clicked()
{
    if ((ui->edit_m->text() == "") || (ui->edit_n->text() == "") || (ui->edit_size_img->text() == ""))
    {
        QMessageBox::information(this, "Error", "Вы не указали один из параметров n, m, img size");
        return;
    }

    QLayoutItem *ch;
    while ((ch = ui->componate_alphabet_buttons->takeAt(0))!= 0)
    {
            ui->componate_alphabet_buttons->removeItem(ch);
            ch->widget()->deleteLater();
            delete ch;
    }

    flag_default = false;
    n = ui->edit_n->text().toInt();
    m = ui->edit_m->text().toInt();
    size_img = ui->edit_size_img->text().toInt();
    create_images();
}

void root_window::create_images()
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            QPB_modify *pb = new QPB_modify;
            pb->i = i;
            pb->j = j;
            if (flag_default == true)
                pb->str = messege[j + i*n];

            QSize button_size(50,50);
            pb->setMaximumSize(button_size);
            pb->setMinimumSize(button_size);

            pb->setIcon(QIcon(":/images/question.png"));
            QSize icon_size(40,40);
            pb->setIconSize(icon_size);

            connect(pb, &QPushButton::clicked, [this, pb](){
                QMessageBox::information(this, "test", pb->str);
            });
            ui->componate_alphabet_buttons->addWidget(pb, i, j);
        }
}

void root_window::on_button_default_clicked()
{
    n = 5;
    m = 5;
    size_img = 100;
    flag_default = true;
    set_default_messege();
    create_images();

    ui->edit_m->setText("5");
    ui->edit_n->setText("5");
    ui->edit_size_img->setText("100");
}

void root_window::set_default_messege()
{
    QString text[25] = {"Жёлудь", "и", "дерево", "красовались", "около", "ворот", "аббатства",
                  "проверка", "квантограббер", "Каллининград", "Берляндский", "Аэропорт",
                  "десять", "часов", "пятнадцать", "минут", "день", "икс", "парад", "с",
                   "флагами", "на", "площади", "близ", "фонтана"};
    for (int i = 0; i < n*m; i++)
        messege.push_back(text[i]);
}

void root_window::on_pushButton_clicked()
{
    QMessageBox::information(this, "", "запускает старт игры + работу с сетью, которую я прокрастинирую");
}
