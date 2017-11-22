#include "make_img_window.h"
#include "ui_make_img_window.h"

extern std::vector<QRgb> colors;
extern std::vector<QImage> runes;

make_img_window::make_img_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::make_img_window)
{
    ui->setupUi(this);
    set_colors();
    set_runes();
    ui->edit_root_messege->setVisible(false);
    ui->lbl_root_show_messege->setVisible(false);
}

make_img_window::~make_img_window()
{
    delete ui;
}

void make_img_window::set_colors()
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    for (int i = 0; i < int(colors.size()); i++)
    {
        QPushButton *pb = new QPushButton;
        QImage temp(100, 100, QImage::Format_RGB32);
        temp.fill(QColor(colors[i]));

        pb->setMaximumSize(50, 50);
        pb->setMinimumSize(50, 50);
        pb->setIcon(QIcon(QPixmap::fromImage(temp)));
        pb->setIconSize(pb->size());
        connect(pb, &QPushButton::clicked, [this, pb](){
            if(!flag_img_choosen)
                QMessageBox::information(this, "error", "Выберите изображение (справа), да там, еще можно двигать ползунок");
            else
            {
                QImage find_color = pb->icon().pixmap(pb->size()).toImage();
                QImage temp = paint_picture(ui->lbl_created_img->pixmap()->toImage(),
                                             find_color.pixel(1, 1));
                ui->lbl_created_img->setPixmap(QPixmap::fromImage(temp));
            }
        });

        hbox->addWidget(pb);
    }

    ui->scroll_color_content->setLayout(hbox);
}

void make_img_window::set_runes()
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    for (int i = 0; i < int(runes.size()); i++)
    {
        QPushButton *pb = new QPushButton;

        pb->setMaximumSize(80, 80);
        pb->setMinimumSize(80, 80);
        pb->setIcon(QIcon(QPixmap::fromImage(runes[i])));
        pb->setIconSize(pb->size());
        connect(pb, &QPushButton::clicked, [this, pb](){
            QSize size = pb->size();
            flag_img_choosen = true;
            // Данная строка устанавливает изображение с иконки кнопки и растягивает его (если кому влом вникать)
            ui->lbl_created_img->setPixmap(pb->icon().pixmap(size).scaled(ui->lbl_created_img->size()));
        });

        vbox->addWidget(pb);
    }

    ui->scroll_rune_content->setLayout(vbox);
}

void make_img_window::on_button_cancel_clicked()
{
    emit this->reject();
    this->close();
}

void make_img_window::on_button_ok_clicked()
{
    QImage img = ui->lbl_created_img->pixmap()->toImage().scaled(100, 100);
    if (flag_is_it_root)
    {
        emit this->root_make_new_img(img, root_i, root_j, ui->edit_root_messege->text());
    }
    else
        emit this->i_make_img(img);

    this->close();
}

QImage make_img_window::paint_picture (QImage img, QRgb color)
//позаимствовала и видоизменила функцию шифрования
//пусть будет просто цвет, а в вызове функции укажем, какой именно элемент массива цветов надо брать
{
    //выпиливаем изначально нужный цвет
    QImage data = img;
    QRgb white = qRgb(255,255,255);

    int wid = data.width();
    int hei = data.height();

    for (int i = 0; i < wid*hei; i++)
    {
        QRgb temp = data.pixel(i%wid, i/wid);

        if (temp!=white) //исключаем белый цвет (фон букв)
            data.setPixel(i%wid, i/wid, color);
    }

    return data;
}

void make_img_window::set_rune(QImage img, int i, int j, QString str)
{
    ui->lbl_created_img->setPixmap(QPixmap::fromImage(img).scaled(ui->lbl_created_img->size()));
    root_i = i;
    root_j = j;
    flag_is_it_root = true;
    flag_img_choosen = true;
    ui->edit_root_messege->setText(str);

    ui->edit_root_messege->setVisible(true);
    ui->lbl_root_show_messege->setVisible(true);
}
