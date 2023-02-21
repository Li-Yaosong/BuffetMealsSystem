#ifndef COMMON_H
#define COMMON_H
#include <QString>
#include <QVariant>
#include "stylesheet.h"
class Common
{
public:
    struct Dish
    {
        QString name;
        int number;
        double price;
        QByteArray image;
        QString storage;
    };
    Common();
    static Dish mapToDish(QMap<QString, QVariant> data);
    static QPixmap creatImage(QByteArray data);
};

#endif // COMMON_H
