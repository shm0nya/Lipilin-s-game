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

    void create_images();                               // Создает кнопки в окне

    void set_temp_rune(QImage img) {temp_rune = img;}   // Костыль. Ставит руну созданную в make_rune

    void set_rune_at_GL(QPB_modify *pb, int i, int j);  // Установка руны в сетке рун, после её создания в mainwindow

    bool get_default_flag() {return flag_default;}      // Запрос флага (поумолчанию или нет?) - вдруг кто-то сам решит задать

    QString get_messege_at_position(int i, int j);      // Получение сообщения, соответствующего позиции в mainwindow

    QImage get_rune_at_position(int i, int j);          // Передает руну на определенной позиции в mainwindow

    int get_n() {return n;}                             // Передает n в mainwindow

    int get_m() {return m;}                             // Передает m в mainwindow

private slots:
    void on_button_apply_clicked();                     // Изменение n, m рутом (пересчет сетки)

    void on_button_default_clicked();                   // Возврат к дефолтным настройкам

    void on_button_start_clicked();                       //

signals:
    void get_rune(int);                                         // Сигнал "дай мне руну" (шлется в make_img), там есть vector с рунами
    void show_make_img_with_my_img(QImage, int, int, QString);  // Смена окон
    void start();                                               // Старт игры

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

    std::vector<QString> messege = default_text;    // Сообщение, которое закодировано рунами (изначально равно default_text)
    QImage temp_rune;                               // Костыль
    std::vector<std::vector<QPB_modify*>> pb_runes; // Массив с указателями на руны (сразу надо было делать везде)
};

#endif // ROOT_WINDOW_H
