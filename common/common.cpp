#include "common.h"
#include <QPixmap>

Common::Common()
{

}

Common::Dish Common::mapToDish(QMap<QString, QVariant> data)
{
    Dish dishInfo;
    dishInfo.name = data.value("name").toString();
    dishInfo.className = data.value("class").toString();
    dishInfo.price = data.value("price").toDouble();
    dishInfo.image = data.value("image").toByteArray();
    dishInfo.storage = data.value("storage").toString();
    return dishInfo;
}

QPixmap Common::creatImage(QByteArray data)
{
    QPixmap photo;
    photo.loadFromData(data, "JPG");
    return photo;
}
