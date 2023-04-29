#ifndef COMMON_H
#define COMMON_H
#include <QString>
#include <QVariant>
#include "global.h"
#include "connectservice.h"
#define Service ConnectService::service()
namespace Common {
    Dish mapToDish(QMap<QString, QVariant> data);
    QMap<QString, QByteArray> dishToMap(Dish dish);
    QPixmap creatImage(QByteArray data);
    double calculateTotal(QMap<QString, double> priceMap, QMap<QString, int> dishesMap);
};

#endif // COMMON_H
