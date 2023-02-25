#ifndef CONNECTSERVICE_H
#define CONNECTSERVICE_H
#include "rep_service_replica.h"
#include <QObject>

class ConnectService
{
public:
    ConnectService();
    QMap<QString, QList<QMap<QString, QVariant> > > getData();
    QMap<QString, QVariant> getClass();
    void addDishes(QMap<QString, QByteArray> map);
    void addClass(QMap<QString, QByteArray> map);
    void addOrder(QMap<QString, QByteArray> map);
    void delDishes(QStringList delList);
private:
    ServiceReplica *m_rep;
};

#endif // CONNECTSERVICE_H
