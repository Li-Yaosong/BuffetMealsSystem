#include "connectservice.h"

ConnectService::ConnectService()
{
    QRemoteObjectNode *repNode=new QRemoteObjectNode();
    repNode->connectToNode(QUrl("local:9000"));
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
