#ifndef CONNECTSERVICE_H
#define CONNECTSERVICE_H
#include "rep_service_replica.h"
#include <QObject>

class ConnectService
{
public:
    ConnectService();
    QByteArray getData();
private:
    ServiceReplica *m_rep;
};

#endif // CONNECTSERVICE_H
