/* Mode = player & root;
 * Окно используется как первым, так и вторым
 * Пользователь создает новую руну, после чего из окна шлется сигнал void i_make_img(QImage)
 * сигнал ловится mainwindow, который в зависимости от пользователя интерпретирует сигнал
*/

#ifndef MAKE_IMG_WINDOW_H
#define MAKE_IMG_WINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>

#include <string>
#include <vector>

namespace Ui {
class make_img_window;
}

class make_img_window : public QDialog
{
    Q_OBJECT

public:
    explicit make_img_window(QWidget *parent = 0);
    ~make_img_window();

    void set_colors(); /* Ставит pushbuttons с икноками всех возможных цветов (vector<QRGB> colors) */
    void set_runes();

    QImage get_rune(int i) {return runes[i%runes.size()];}
    QRgb get_color(int i) {return colors[i%colors.size()];}
    QImage paint_picture (QImage data, QRgb color); /* Окрашивает руну из data в цвет color */
    void set_rune(QImage img, int i, int j, QString str);

private slots:
    void on_button_cancel_clicked();
    void on_button_ok_clicked();

signals:
    void i_make_img(QImage);/* Вызывается, как пользователь закончил создавать изображение, передает созданное изображение */
    void root_make_new_img(QImage, int, int, QString);

private:
    Ui::make_img_window *ui;

    bool flag_img_choosen;
    bool flag_is_it_root = false;

    //хранилище цветов
    // Цвета, где есть 0 и 255 являются вырожденными (см способ шифровния S) или делай свой
    std::vector<QRgb> colors =
    {
        qRgb(128, 15, 15), //красный
        qRgb(15, 128, 15), //синий
        qRgb(15, 15, 128), //зеленый
        qRgb(128, 128, 15), //желтый
        qRgb(128, 15, 128), //фиолетовый
        qRgb(15, 128, 128), //морская волна
    };

    std::vector<QImage> runes =
    {
        QImage(":/runes/a.png"),
        QImage(":/runes/b.png"),
        QImage(":/runes/c.png"),
        QImage(":/runes/ch.png"),
        QImage(":/runes/d.png"),
        QImage(":/runes/e.png"),
        QImage(":/runes/h.png"),
        QImage(":/runes/i.png"),
        QImage(":/runes/k.png"),
        QImage(":/runes/l.png"),
        QImage(":/runes/m.png"),
        QImage(":/runes/n.png"),
        QImage(":/runes/o.png"),
        QImage(":/runes/p.png"),
        QImage(":/runes/r.png"),
        QImage(":/runes/t.png"),
        QImage(":/runes/u.png"),
        QImage(":/runes/v.png"),
    };

    int root_i;
    int root_j;
};

#endif // MAKE_IMG_WINDOW_H
