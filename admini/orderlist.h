#ifndef ORDERLIST_H
#define ORDERLIST_H

#include <QWidget>
#include "global.h"
namespace Ui {
class OrderList;
}

class OrderList : public QWidget
{
    Q_OBJECT

public:
    explicit OrderList(Order order, QWidget *parent = nullptr);
    ~OrderList();
signals:
    void updateOrder();
private slots:
    void on_see_pushButton_clicked();

private:
    Ui::OrderList *ui;
    QMap<QString, int> m_dishes;
    int m_num;
};

#endif // ORDERLIST_H
