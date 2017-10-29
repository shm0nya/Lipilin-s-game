/* Mode = player
 * Данный объект унаследован от от QPushButton
 * Предназначен для того, чтобы хранить свою позицию в QGridLayout и другую информацию
*/

#ifndef QPB_MODIFY_H
#define QPB_MODIFY_H

#include <QPushButton>
#include <QImage>
#include <QString>

class QPB_modify : public QPushButton
{
    Q_OBJECT
public:
    explicit QPB_modify(QPushButton *parent = nullptr);
    /*#! Кому охота делайте методы set и get */
    QImage reverse_img; // Изображение
    int i; // Координата
    int j; // Координата j
    bool was_opening; // Флаг: открыто или нет
    QString str;

};

#endif // QPB_MODIFY_H
