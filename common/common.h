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
        QString className;
        double price;
        QByteArray image;
        QString storage;
    };
    Common();
    static Dish mapToDish(QMap<QString, QVariant> data);
    static QPixmap creatImage(QByteArray data);
    static double calculateTotal(QMap<QString, double> priceMap, QMap<QString, int> dishesMap);
};

#endif // COMMON_H
