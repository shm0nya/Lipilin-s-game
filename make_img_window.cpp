#include "make_img_window.h"
#include "ui_make_img_window.h"

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
