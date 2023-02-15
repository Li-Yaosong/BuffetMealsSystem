#ifndef CONNECTSERVICE_H
#define CONNECTSERVICE_H
#include "rep_service_replica.h"
#include <QObject>

class ConnectService
{
public:
    ConnectService();
    QMap<int, QMap<QString, QVariant> > getData();
    void addDishes(QMap<QString, QByteArray> map);
    void delDishes(QStringList delList);
private:
    ServiceReplica *m_rep;
};

#endif // CONNECTSERVICE_H
