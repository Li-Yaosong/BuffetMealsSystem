#include "connectservice.h"
#include "qurl.h"

ConnectService::ConnectService()
{
    QRemoteObjectNode *repNode=new QRemoteObjectNode();
    repNode->connectToNode(QUrl("local:9000"));
    m_rep = repNode->acquire<ServiceReplica>();
    m_rep->waitForSource(500);
}

ConnectService *ConnectService::service()
{
    return new ConnectService();
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

void ConnectService::addDishes(const Dish & dishInfo)
{
    m_rep->addDishes(dishInfo);
}

void ConnectService::modifiDishe(const Dish &dishInfo, const QString &old)
{
    m_rep->modifiDishe(dishInfo,old);
}

void ConnectService::addClass(Class map)
{
    m_rep->addClass(map);
}

void ConnectService::addOrder(QMap<QString, QByteArray> map)
{
    m_rep->addOrder(map);
}

void ConnectService::updateOrder(int num, int state)
{
    m_rep->updateOrder(num, state);
}

void ConnectService::delDishes(QStringList delList)
{
    m_rep->delDishes(delList);
}

QStringList ConnectService::classes()
{

    return getClass().keys();
}
