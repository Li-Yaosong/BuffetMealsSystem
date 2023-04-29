#ifndef CONNECTSERVICE_H
#define CONNECTSERVICE_H
#include "rep_service_replica.h"
#include <QObject>
//#include "libbms_global.h"
class ConnectService
{
public:

    static ConnectService *service();
    QMap<QString, QList<Dish>> getData();
    QMap<QString, QVariant> getClass();
    QList<Order> getOrder();
    void addDishes(const Dish &dishInfo);
    void modifiDishe(const Dish &dishInfo, const QString &old);
    void addClass(Class map);
    void addOrder(QMap<QString, QByteArray> map);
    void updateOrder(int num, int state);
    void delDishes(QStringList delList);
    QStringList classes();
private:
    ConnectService();
    ServiceReplica *m_rep;
};

#endif // CONNECTSERVICE_H
