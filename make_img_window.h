#ifndef MAKE_IMG_WINDOW_H
#define MAKE_IMG_WINDOW_H

#include <QDialog>

namespace Ui {
class make_img_window;
}

class make_img_window : public QDialog
{
    Q_OBJECT

public:
    explicit make_img_window(QWidget *parent = 0);
    ~make_img_window();

private:
    Ui::make_img_window *ui;
};

#endif // MAKE_IMG_WINDOW_H
