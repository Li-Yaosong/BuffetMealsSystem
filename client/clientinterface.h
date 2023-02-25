#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <QWidget>
#include <QTcpSocket>
#include <QPushButton>
namespace Ui {
class ClientInterface;
}
class ConnectService;
class CDishWidget;
class PlaceOrder;
class ListWidget;
class TabWidget;
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
    void addDishes(QPair<QString, int> dish);
    void placeOrder();
    void on_pushButton_placeOrder_clicked();

private:
    void updateClassList();
    Ui::ClientInterface *ui;
    ConnectService *m_service;
    QList<CDishWidget *> m_dishWidgetList;
    //座位号
    int m_seat;
    QTcpSocket *m_tcpsocket;
    PlaceOrder *m_placeOrder;
    QMap<QString, int> m_orderMap;
    ListWidget *m_allDishList;
    TabWidget *m_classTab;
    QStringList m_classList;
    QList<QPushButton *> m_classButtonList;
    QMap<QString, CDishWidget *> m_dishWidgetMap;
};

#endif // CLIENTINTERFACE_H
