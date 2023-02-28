#include "connectservice.h"
#include "qurl.h"

ConnectService::ConnectService()
{
    QRemoteObjectNode *repNode=new QRemoteObjectNode();
    repNode->connectToNode(QUrl("tcp://192.168.1.12:9000"));
    m_rep = repNode->acquire<ServiceReplica>();
    m_rep->waitForSource(500);
}

QMap<QString, QList<QMap<QString, QVariant>>> ConnectService::getData()
{
    QRemoteObjectPendingReply<QByteArray> data = m_rep->getAllDishes();

    data.waitForFinished();
    QByteArray byte = data.returnValue();
    QDataStream Data(byte);
    QMap<QString, QList<QMap<QString, QVariant>>> re;
    Data >> re;
    return re;
}

QMap<QString, QVariant> ConnectService::getClass()
{
    QRemoteObjectPendingReply<QByteArray> data = m_rep->getAllClass();

    data.waitForFinished();
    QByteArray byte = data.returnValue();
    QDataStream Data(byte);
    QMap<QString, QVariant> re;
    Data >> re;
    return re;
}

void ConnectService::addDishes(QMap<QString, QByteArray> map)
{
    m_rep->addDishes(map);
}

void ConnectService::addClass(QMap<QString, QByteArray> map)
{
    m_rep->addClass(map);
}

void ConnectService::addOrder(QMap<QString, QByteArray> map)
{
    m_rep->addOrder(map);
}

void ConnectService::delDishes(QStringList delList)
{
    m_rep->delDishes(delList);
}
