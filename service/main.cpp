#include "service.h"

#include <QApplication>
#include <QRemoteObjectHost>
#include "service.h"
#include <QHostInfo>

QString localip()
{
    //获取IPv4地址
    QString hostname = QHostInfo::localHostName();
    QHostInfo hostinfo = QHostInfo::fromName(hostname);
    QString localip = "";
    QList<QHostAddress> addList = hostinfo.addresses();
    if(!addList.isEmpty())
    {

        for(int i = 0;i<addList.size();i++)
        {
            QHostAddress aHost = addList.at(i);
            if(QAbstractSocket::IPv4Protocol == aHost.protocol())
            {
                return aHost.toString();
                break;
            }
        }
    }
    return QString();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Service *service=new Service;
    QRemoteObjectHost *srcNode = new QRemoteObjectHost(QUrl("tcp://"+localip()+":9000"));
    //获取IPv4地址
    QString hostname = QHostInfo::localHostName();
    QHostInfo hostinfo = QHostInfo::fromName(hostname);
    QString localip = "";
    QList<QHostAddress> addList = hostinfo.addresses();
    if(!addList.isEmpty())
    {

        for(int i = 0;i<addList.size();i++)
        {
            QHostAddress aHost = addList.at(i);
            if(QAbstractSocket::IPv4Protocol == aHost.protocol())
            {
                localip = aHost.toString();
                break;
            }
        }
    }
    qDebug()<<localip;
    srcNode->enableRemoting(service);
    return a.exec();
}

