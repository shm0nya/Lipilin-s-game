#ifndef CHOOSE_BUTTON_H
#define CHOOSE_BUTTON_H

#include <QDialog>
#include <QImage>
#include <QMessageBox>
#include <vector>
#include "qpb_modify.h"



namespace Ui {
class choose_button;
}

class choose_button : public QDialog
{
    Q_OBJECT

public:
    explicit choose_button(QWidget *parent = 0);
    ~choose_button();
    void set_button (QPB_modify *pb, int i, int j);
    void open_button(QImage img, int i, int j);

private:
    Ui::choose_button *ui;

signals:
    void i_choose_img(QImage);
    void close_wnd();

private slots:
    void on_button_cancel_clicked();
};

#endif // CHOOSE_BUTTON_H
