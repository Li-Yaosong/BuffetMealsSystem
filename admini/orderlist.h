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
    void updateReport();
private slots:
    void on_see_pushButton_clicked();

private:
    Ui::OrderList *ui;
    QMap<QString, int> m_dishes;
    QString m_date = "";
    double m_total = 0;
    int m_state = 0;
    int m_num = 0;
};

#endif // ORDERLIST_H
