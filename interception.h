#ifndef INTERCEPTION_H
#define INTERCEPTION_H

#include <QDialog>

namespace Ui {
class interception;
}

class interception : public QDialog
{
    Q_OBJECT

signals:
    void homecomig(); // Угадайте пасхалку

public:
    explicit interception(QWidget *parent = 0);
    ~interception();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::interception *ui;
};

#endif // INTERCEPTION_H
