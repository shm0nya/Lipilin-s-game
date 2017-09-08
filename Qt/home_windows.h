#ifndef HOME_WINDOWS_H
#define HOME_WINDOWS_H

#include <QWidget>

namespace Ui {
class Home_windows;
}

class Home_windows : public QWidget
{
    Q_OBJECT

public:
    explicit Home_windows(QWidget *parent = 0);
    ~Home_windows();
    void setLogin(const QString& str_login);
    QString takeLogin() const { return login_name; }

private:
    Ui::Home_windows *ui;
    QString login_name;
};

#endif // HOME_WINDOWS_H
