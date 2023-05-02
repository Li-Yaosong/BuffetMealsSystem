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
class ClassButton;
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

    void on_pushButton_placeOrder_clicked();

    void on_pushButton_setSeatNum_clicked();

    void on_pushButton_refresh_clicked();

private:
    void updateClassList();
    void initStyle();
    Ui::ClientInterface *ui;
    QList<CDishWidget *> m_dishWidgetList;
    //座位号
    int m_seat;
    QTcpSocket *m_tcpsocket;
    PlaceOrder *m_placeOrder;
    QMap<QString, int> m_orderMap;
    ListWidget *m_allDishList;
    TabWidget *m_classTab;
    QStringList m_classList;
    QList<ClassButton *> m_classButtonList;
    QMap<QString, CDishWidget *> m_dishWidgetMap;
    ClassButton *m_allClassButton;
};

#endif // CLIENTINTERFACE_H
