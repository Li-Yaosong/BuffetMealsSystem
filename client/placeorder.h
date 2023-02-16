#ifndef PLACEORDER_H
#define PLACEORDER_H

#include <QObject>
class PlaceOrderP;
class PlaceOrder : public QObject
{
    Q_OBJECT
public:
    PlaceOrder(const QString &ip, const quint16 &port);
    void orderInfo(const QByteArray &order);
private:
    PlaceOrderP * const p;
};

#endif // PLACEORDER_H
