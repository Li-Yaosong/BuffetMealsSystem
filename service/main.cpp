#include "service.h"

#include <QApplication>
#include <QRemoteObjectHost>
#include "service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Service *service=new Service;
    QRemoteObjectHost *srcNode = new QRemoteObjectHost(QUrl("local:9000"));
    srcNode->enableRemoting(service);
    return a.exec();
}
