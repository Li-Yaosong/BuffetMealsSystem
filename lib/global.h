#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QVariant>
#include <QMetaType>
struct Dish
{
    QString name;
    QString className;
    double price = 0;
    QByteArray image;
    int storage = 0;
    operator QVariant() const
    {
    return QVariant::fromValue(*this);
    }
    inline friend QDataStream& operator<<(QDataStream& out, const Dish& d)
    {
    out << d.name;
    out << d.className;
    out << QString::number(d.price);
    out << d.image;
    out << QString::number(d.storage);
    return out;
    }
    inline friend  QDataStream& operator>>(QDataStream& in, Dish & d)
    {
    QString price;
    QString storage;
    in >> d.name;
    in >> d.className;
    in >> price;
    d.price = price.toDouble();
    in >> d.image;
    in >> storage;
    d.storage = storage.toInt();
    return in;
    }
};
struct Class
{
    QString name;
    QByteArray image;
    inline friend QDataStream& operator<<(QDataStream& out, const Class& c)
    {
    out << c.name;
    out << c.image;
    return out;
    }
    inline friend  QDataStream& operator>>(QDataStream& in, Class & c)
    {
    in>>c.name;
    return in;
    }
};
struct Order
{
    int num = 0;
    int seat = 0;
    QString time;
    double total = 0;
    QByteArray dishes;
    int state = 0;
    operator QVariant() const
    {
    return QVariant::fromValue(*this);
    }
    inline friend QDataStream& operator<<(QDataStream& out, const Order& d)
    {
    out << QString::number(d.num);
    out << QString::number(d.seat);
    out << d.time;
    out << QString::number(d.total);
    out << d.dishes;
    out << QString::number(d.state);
    return out;
    }
    inline friend  QDataStream& operator>>(QDataStream& in, Order & d)
    {
        QString num;
        QString seat;
        QString total;
        QString state;

        in >> num;
        in >> seat;
        d.num = num.toInt();
        d.seat = seat.toInt();
        in >> d.time;
        in >> total;
        d.total = total.toDouble();
        in >> d.dishes;
        in >> state;
        d.state = state.toInt();
        return in;
    }
};
class ClassList : public QList<Class>
{
public:
    inline ClassList() noexcept { }
    inline explicit ClassList(const QList<Class> &l) :QList<Class>(l){}
    inline QStringList nameList();

};

inline QStringList ClassList::nameList()
{
    QStringList list;
    for(const Class &classInfo : qAsConst(*this))
    {
        list.append(classInfo.name);
    }
    return list;
}

Q_DECLARE_METATYPE(Dish);
Q_DECLARE_METATYPE(Class);
Q_DECLARE_METATYPE(Order);
Q_DECLARE_METATYPE(ClassList);
#endif
