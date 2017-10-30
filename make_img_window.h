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

    vector<QRgb> PaintPicture (vector<QRgb> &data, QRgb &color); /* Mode: player
                                                                 Окрашивает руну из data в цвет color */

private:
    Ui::make_img_window *ui;

    std::vector<QRgb> colors; //хранилище цветов
};

#endif // MAKE_IMG_WINDOW_H
