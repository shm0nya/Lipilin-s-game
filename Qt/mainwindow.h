#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <home_windows.h>

extern QString name_login;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /*
     * Два слота. Первый проверка на правильность ввода
     * Второй - открытие основных окон.
    */
    void ok_enabled();
    void on_Login_button_clicked();

private:
    Ui::MainWindow *ui;
    Home_windows *sWindow;
};

#endif // MAINWINDOW_H
