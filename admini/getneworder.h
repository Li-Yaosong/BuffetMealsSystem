#ifndef GETNEWORDER_H
#define GETNEWORDER_H
#include <QObject>

class GetNewOrderP;
class GetNewOrder : public QObject
{
    Q_OBJECT
public:
    GetNewOrder();
signals:
    void hasNewOrder(QByteArray order);
private:
    GetNewOrderP * const p;
};

#endif // GETNEWORDER_H
