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
    bool registerAccount(const Account &account);
    bool accountVerification(const Account &account);
    QMap<QString, QList<Dish>> getData();
    QMap<QString, QVariant> getClass();
    QList<Order> getOrder();
    QList<Report> getDailyReport(const QString &date = "");
    QList<Report> getMonthlyReport(const QString &date = "");
    QStringList classes();
private:
    ConnectService();
    static ConnectService *m_service;
    ServiceReplica *m_rep;
};

#endif // CONNECTSERVICE_H
