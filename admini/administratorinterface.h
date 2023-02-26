#ifndef ADMINISTRATORINTERFACE_H
#define ADMINISTRATORINTERFACE_H

#include "connectservice.h"

#include <QWidget>

#include<QTcpServer>//监听套接字
#include<QTcpSocket>//通信套接字
namespace Ui {
class AdministratorInterface;
}
class DishWidget;
class ListWidget;
class TabWidget;
class QPushButton;
class AdministratorInterface : public QWidget
{
    Q_OBJECT

public:
    explicit AdministratorInterface(QWidget *parent = nullptr);
    ~AdministratorInterface();
    void updateDishesList();
    void updateClassList();
    void updateOrderList();

private slots:
    void on_pushButton_addDishes_clicked();

    void on_pushButton_addClass_clicked();

    void setDelList(QString name, bool del);

    void hasNewOrder(QByteArray order);

    void on_pushButton_orderManage_clicked();

    void on_pushButton_dishManage_clicked();

    void on_pushButton_history_clicked();

    void on_pushButton_test_clicked();

private:
    void initStyle();
    Ui::AdministratorInterface *ui;
    ConnectService *m_service;
    QList<DishWidget *> m_dishWidgetList;
    QList<QString> m_delList;
    ListWidget *m_allDishList;
    TabWidget *m_classTab;
    TabWidget *m_orderTab;
    ListWidget *m_newOrderList;
    ListWidget *m_finishOrderList;
    QStringList m_classList;
    QList<QPushButton *> m_classButtonList;
    //价格表Map
    QMap<QString, double> m_priceMap;
};

#endif // ADMINISTRATORINTERFACE_H
