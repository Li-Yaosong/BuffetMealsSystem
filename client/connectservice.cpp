#include "connectservice.h"

ConnectService::ConnectService()
{
    QRemoteObjectNode *repNode=new QRemoteObjectNode();
    repNode->connectToNode(QUrl("local:9000"));
    m_rep = repNode->acquire<ServiceReplica>();
    m_rep->waitForSource();
}

QByteArray ConnectService::getData()
{
    QRemoteObjectPendingReply<QByteArray> data = m_rep->showImage();
    data.waitForFinished(100);
    return data.returnValue();
}
