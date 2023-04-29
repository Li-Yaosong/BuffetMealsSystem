#ifndef CONNECTSERVICE_H
#define CONNECTSERVICE_H
#include "rep_service_replica.h"
#include <QObject>
//#include "libbms_global.h"
class ConnectService
{
public:

    static ConnectService *service();
    ServiceReplica *rep();
    QMap<QString, QList<Dish>> getData();
    QMap<QString, QVariant> getClass();
    QList<Order> getOrder();
    QStringList classes();
private:
    ConnectService();
    static ConnectService *m_service;
    ServiceReplica *m_rep;
};

#endif // CONNECTSERVICE_H
