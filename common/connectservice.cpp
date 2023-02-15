#include "connectservice.h"
#include "qurl.h"

ConnectService::ConnectService()
{
    QRemoteObjectNode *repNode=new QRemoteObjectNode();
    repNode->connectToNode(QUrl("tcp://192.168.52.128:9000"));
    m_rep = repNode->acquire<ServiceReplica>();
    m_rep->waitForSource(500);
}

QMap<int, QMap<QString, QVariant>> ConnectService::getData()
{
//    QRemoteObjectPendingReply<QByteArray> data = m_rep->showImage();
//    data.waitForFinished(100);
//    QByteArray d = data.returnValue();
//    return data.returnValue();
    QRemoteObjectPendingReply<QByteArray> data = m_rep->getAllDishes();

    data.waitForFinished(500);
    QByteArray byte = data.returnValue();
    QDataStream Data(byte);
    QMap<int, QMap<QString, QVariant>> re;
    Data >> re;
    return re;
}

void ConnectService::addDishes(QMap<QString, QByteArray> map)
{
    m_rep->addDishes(map);
}

void ConnectService::delDishes(QStringList delList)
{
    m_rep->delDishes(delList);
}
