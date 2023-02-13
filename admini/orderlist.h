#ifndef ORDERLIST_H
#define ORDERLIST_H

#include <QWidget>

namespace Ui {
class OrderList;
}

class OrderList : public QWidget
{
    Q_OBJECT

public:
    explicit OrderList(QWidget *parent = nullptr);
    ~OrderList();

private:
    Ui::OrderList *ui;
};

#endif // ORDERLIST_H
