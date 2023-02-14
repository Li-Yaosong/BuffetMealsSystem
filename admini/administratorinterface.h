#ifndef ADMINISTRATORINTERFACE_H
#define ADMINISTRATORINTERFACE_H

#include "connectservice.h"
#include <QWidget>

namespace Ui {
class AdministratorInterface;
}
class DishWidget;
class AdministratorInterface : public QWidget
{
    Q_OBJECT

public:
    explicit AdministratorInterface(QWidget *parent = nullptr);
    ~AdministratorInterface();
    void updateDishesList();

private slots:
    void on_noFinished_pushButton_clicked();

    void on_pushButton_addDishes_clicked();

    void setDelList(QString name, bool del);


    void on_pushButton_4_clicked();

private:
    Ui::AdministratorInterface *ui;
    ConnectService *m_service;
    QList<DishWidget *> m_dishWidgetList;
    QList<QString> m_delList;
};

#endif // ADMINISTRATORINTERFACE_H
