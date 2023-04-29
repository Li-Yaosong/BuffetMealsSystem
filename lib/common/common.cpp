#include "common.h"
#include <QPixmap>

Dish Common::mapToDish(QMap<QString, QVariant> data)
{
    Dish dishInfo;
    dishInfo.name = data.value("name").toString();
    dishInfo.className = data.value("class").toString();
    dishInfo.price = data.value("price").toDouble();
    dishInfo.image = data.value("image").toByteArray();
    dishInfo.storage = data.value("storage").toInt();
    return dishInfo;
}

QMap<QString, QByteArray> Common::dishToMap(Dish dish)
{
    return QMap<QString, QByteArray>{
        {"name", dish.name.toUtf8()},
        {"class", dish.className.toUtf8()},
        {"price", QString::number(dish.price).toUtf8()},
        {"image", dish.image},
        {"storage", QString::number(dish.storage).toUtf8()}
    };
}

QPixmap Common::creatImage(QByteArray data)
{
    QPixmap photo;
    photo.loadFromData(data, "JPG");
    return photo;
}

double Common::calculateTotal(QMap<QString, double> priceMap, QMap<QString, int> dishesMap)
{
    double total = 0;
    for(const QString &name : dishesMap.keys())
    {
        total+=priceMap.value(name) * dishesMap.value(name);
    }
    return total;
}
