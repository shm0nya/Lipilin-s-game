#ifndef QPB_MODIFY_H
#define QPB_MODIFY_H

#include <QPushButton>
#include <QImage>

class QPB_modify : public QPushButton
{
    Q_OBJECT
public:
    explicit QPB_modify(QPushButton *parent = nullptr);
    void set_reverse_img(QImage img){reverse_img = img;}
    QImage get_reverse_img(){return reverse_img;}
private:
    QImage reverse_img;
};

#endif // QPB_MODIFY_H
