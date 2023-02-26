#include "placeorder.h"
#include <QTcpSocket>
class PlaceOrderP : public QObject
{
public:
    PlaceOrderP(const QString &ip, const quint16 &port)
        :m_ip(ip),
        m_port(port),
        m_tcpsocket(new QTcpSocket(this))
    {
        m_tcpsocket->connectToHost(m_ip, m_port);
    }
    QString ip()
    {
        return m_ip;
    }
    quint16 port()
    {
        return m_port;
    }
    void write(const QByteArray &order)
    {
        m_tcpsocket->write(order);
    }
private:
    QString m_ip;
    quint16 m_port;
    QTcpSocket *m_tcpsocket;
};

PlaceOrder::PlaceOrder(const QString &ip, const quint16 &port)
    :p(new PlaceOrderP(ip, port))
{
//    QString str ="hello!";
}

void PlaceOrder::orderInfo(const QByteArray &order)
{
    p->write(order);
}
