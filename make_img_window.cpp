#include "make_img_window.h"
#include "ui_make_img_window.h"
#include <vector>

std::vector<QRgb> colors=
    {
        qRgb(255,0,0), //красный
        qRgb(0,255,0), //синий
        qRgb(0,0,255), //зеленый
        qRgb(255,255,0), //желтый
        qRgb(255,0,255), //фиолетовый
        qRgb(0,255,255) //морская волна
    }; //хранилище цветов

make_img_window::make_img_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::make_img_window)
{
    ui->setupUi(this);
}

make_img_window::~make_img_window()
{
    delete ui;
}
