#ifndef ROOT_WINDOW_H
#define ROOT_WINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QPushButton>
#include <QLayout>

#include <vector>

#include <qpb_modify.h>

namespace Ui {
class root_window;
}

class root_window : public QDialog
{
    Q_OBJECT

public:
    explicit root_window(QWidget *parent = 0);
    ~root_window();
    void create_images();
    void set_default_messege();

private slots:
    void on_button_apply_clicked();

    void on_button_default_clicked();

    void on_pushButton_clicked();

private:
    Ui::root_window *ui;
    int n = 5;
    int m = 5;
    int size_img = 100;
    std::vector<QString> messege;
    bool flag_default = true;
};

#endif // ROOT_WINDOW_H
