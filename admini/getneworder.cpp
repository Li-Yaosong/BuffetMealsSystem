#include "getneworder.h"
#include <QTcpServer>
#include <QTcpSocket>
class GetNewOrderP
{
public:
    GetNewOrderP(QObject *obj)
        :m_tcpserver(new QTcpServer(obj))
    {
        m_tcpserver->listen(QHostAddress::Any,8888);
    }
    void setSocket(QTcpSocket *socket)
    {
        m_tcpsocket = socket;
    }
    QTcpSocket *socket()
    {
        return m_tcpsocket;
    }
    QTcpServer *server()
    {
        return m_tcpserver;
    }
    QByteArray getNewOrder()
    {
        return m_str;
    }
//public slots:
    void newConnection_slots()
    {
        m_tcpsocket=m_tcpserver->nextPendingConnection();
    }
    void read()
    {
        m_str=m_tcpsocket->readAll();
    }

private:
    QTcpServer *m_tcpserver;
    QTcpSocket *m_tcpsocket;
    QByteArray m_str;
};

GetNewOrder::GetNewOrder()
    :p(new GetNewOrderP(this))
{
    connect(p->server(), &QTcpServer::newConnection, this,[this]{
        p->newConnection_slots();
        connect(p->socket(), &QTcpSocket::readyRead, this, [this]{
            p->read();
            emit hasNewOrder(p->getNewOrder());
        });
    });
}
