/* mode = player
 * Используется для выбора player изображения из отгаданных
 */

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
    void set_button (QPB_modify *pb, int i, int j);     // Устанавливает кнопку в позицию i, j на сетке
    void open_button(QImage img, int i, int j);         // Это вызывается, когда создаётся сетка рун в home_windows (n*m) раз. Создает кнопки в этом окне

private:
    Ui::choose_button *ui;

signals:
    void i_choose_img(QImage, int, int);                // Если руна открыта, то шлется этот сигнал (передает выбранное изображение и его позицию в send_messege)

private slots:
    void on_button_cancel_clicked();                    // Кнопка "назад", возвращает в send_messege
};

#endif // CHOOSE_BUTTON_H
