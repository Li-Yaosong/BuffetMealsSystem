#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <QWidget>
#include<QTcpSocket>
namespace Ui {
class ClientInterface;
}
class ConnectService;
class CDishWidget;
class ClientInterface : public QWidget
{
    Q_OBJECT

public:
    explicit ClientInterface(QWidget *parent = nullptr);
    ~ClientInterface();
    void updateDishesList();
signals:
    void allclean();

private slots:

private:
    Ui::ClientInterface *ui;
    ConnectService *m_service;
    QList<CDishWidget *> m_dishWidgetList;
    //座位号
    int m_seat;
    QTcpSocket *m_tcpsocket;
};

#endif // CLIENTINTERFACE_H
