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
class DishListWidget;
class ClassTabWidget;
class QPushButton;
class AdministratorInterface : public QWidget
{
    Q_OBJECT

public:
    explicit AdministratorInterface(QWidget *parent = nullptr);
    ~AdministratorInterface();
    void updateDishesList();
    void updateClassList();

private slots:
    void on_noFinished_pushButton_clicked();

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
    DishListWidget *m_allDishList;
    ClassTabWidget *m_classTab;
    QStringList m_classList;
    QList<QPushButton *> m_classButtonList;
};

#endif // ADMINISTRATORINTERFACE_H
