#ifndef HOME_WINDOW_H
#define HOME_WINDOW_H
#include <QWidget>
#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>

#include <QPixmap>
#include <QImage>

#include <vector>

#include "qpb_modify.h"
#include "send_messege.h"

using namespace std;

namespace Ui {
class home_window;
}

class home_window : public QWidget
{
    Q_OBJECT

public:
    explicit home_window(QString str_login, QWidget *parent = 0);
    ~home_window();
    void create_img_buttons(vector<vector<QImage>> &cut, int n, int m);

signals:
    void change_wnd_to_swnd();
    void do_it(int, int);
    void i_opend(QImage, int, int);

private slots:
    void on_pushButton_clicked();

private:
    Ui::home_window *ui;
    QImage original_img;
};

vector <vector<QImage>> cut_image(QImage &image, int n, int m);


#endif // HOME_WINDOW_H
