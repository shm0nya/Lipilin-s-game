#ifndef ROOT_WINDOW_H
#define ROOT_WINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QPushButton>
#include <QLayout>
#include <QRgb>

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
    void set_temp_rune(QImage img) {temp_rune = img;}
    void set_rune_at_GL(QPB_modify *pb, int i, int j);
    bool get_default_flag() {return flag_default;}
    QString get_messege_at_position(int i, int j) {return messege[i*n + j];}

private slots:
    void on_button_apply_clicked();

    void on_button_default_clicked();

    void on_pushButton_clicked();

signals:
    void get_rune(int);
    void show_make_img_with_my_img(QImage, int, int);

private:
    Ui::root_window *ui;

    /* Параметры по-умолчанию */
    int n = 5;
    int m = 5;
    std::vector<QString> default_text = {"Жёлудь", "и", "дерево", "красовались", "около",
                        "ворот", "аббатства", "проверка", "квантограббер", "Каллининград",
                        "Берляндский", "Аэропорт", "десять", "часов", "пятнадцать",
                        "минут", "день", "икс", "парад", "с",
                        "флагами", "на", "площади", "близ", "фонтана"};
    bool flag_default = true;

    std::vector<QString> messege = default_text; // Сообщение, которое закодировано рунами (изначально равно default_text)
    QImage temp_rune;
};

#endif // ROOT_WINDOW_H
