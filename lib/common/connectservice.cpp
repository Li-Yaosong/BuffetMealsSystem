#include "connectservice.h"
#include "qurl.h"

ConnectService::ConnectService()
{
    QRemoteObjectNode *repNode=new QRemoteObjectNode();
    repNode->connectToNode(QUrl("local:9000"));
    m_rep = repNode->acquire<ServiceReplica>();
    m_rep->waitForSource(500);
}
ConnectService *ConnectService::m_service = nullptr;
ConnectService *ConnectService::service()
{
    if(!m_service)
    {
        m_service = new ConnectService();
    }
    return m_service;
}

ServiceReplica *ConnectService::rep()
{
    ServiceReplica *rep = m_rep;
    return rep;
}

bool ConnectService::registerAccount(const Account &account)
{
    QRemoteObjectPendingReply<bool> data = m_rep->registerAccount(account);
    data.waitForFinished();
    return data.returnValue();
}

bool ConnectService::accountVerification(const Account &account)
{
    QRemoteObjectPendingReply<bool> data = m_rep->accountVerification(account);
    data.waitForFinished();
    return data.returnValue();
}

QMap<QString, QList<Dish>> ConnectService::getData()
{
    QRemoteObjectPendingReply<QMap<QString, QList<Dish>>> data = m_rep->getAllDishes();
    data.waitForFinished();
    return data.returnValue();
}

QMap<QString, QVariant>  ConnectService::getClass()
{
    QRemoteObjectPendingReply<QMap<QString, QVariant>> data = m_rep->getAllClass();
    data.waitForFinished();
    return data.returnValue();
}

QList<Order> ConnectService::getOrder()
{
    QRemoteObjectPendingReply<QList<Order>> data = m_rep->getOrder();
    data.waitForFinished();
    return data.returnValue();
}

QList<Report> ConnectService::getDailyReport(const QString &date)
{
    QRemoteObjectPendingReply<QList<Report>> data;
    if(date.isEmpty())
    {
        data = m_rep->getDailyReport();
    }
    else
    {
        data = m_rep->getDailyReport(date);
    }

    data.waitForFinished();
    return data.returnValue();
}

QList<Report> ConnectService::getMonthlyReport(const QString &date)
{
    QRemoteObjectPendingReply<QList<Report>> data;
    if(date.isEmpty())
    {
        data = m_rep->getMonthReport();
    }
    else
    {
        data = m_rep->getMonthReport(date);
    }

    data.waitForFinished();
    return data.returnValue();
}

QStringList ConnectService::classes()
{

    return getClass().keys();
}
