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

#include <QUdpSocket>
#include <QMap>

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

    QMap<QString,QString> config();
    void StatusOnline();
    QString takeLogin() const { return login_name; }

signals:
    void change_wnd_to_swnd();
    void do_it(int, int);
    void i_opend(QImage, int, int);

private slots:
    void on_pushButton_clicked();
    void ready();

private:
    Ui::home_window *ui;
    QImage original_img;
    QString login_name; // логин
    QString key; // ключ
    QString level;
    QString iOverhear; // кого пользователь прослушивает
    QList <QString> meOverhear; // кто пользователя прослушивает
    QUdpSocket *soket; //сокет
    QMap<QString,QString> UserList;
};

vector <vector<QImage>> cut_image(QImage &image, int n, int m);


#endif // HOME_WINDOW_H
