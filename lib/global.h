#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QVariant>
#include <QMetaType>
#include <QSqlQuery>
#include <QDate>
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
    out << d.name
        << d.className
        << QString::number(d.price)
        << d.image
        << QString::number(d.storage);
    return out;
    }
    inline friend  QDataStream& operator>>(QDataStream& in, Dish & d)
    {
    QString price, storage;
    in >> d.name >> d.className >> price >> d.image >> storage;
    d.price = price.toDouble();
    d.storage = storage.toInt();
    return in;
    }
};
struct Class
{
    QString name;
    QByteArray image;
    operator QVariant() const
    {
    return QVariant::fromValue(*this);
    }
    inline friend QDataStream& operator<<(QDataStream& out, const Class& c)
    {
    out << c.name
        << c.image;
    return out;
    }
    inline friend  QDataStream& operator>>(QDataStream& in, Class & c)
    {
    in>>c.name >> c.image;
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
        out << QString::number(d.num)
            << QString::number(d.seat)
            << d.time
            << QString::number(d.total)
            << d.dishes
            << QString::number(d.state);
        return out;
    }
    inline friend  QDataStream& operator>>(QDataStream& in, Order & d)
    {
        QString num, seat, total, state;
        in >> num>> seat>> d.time>> total>> d.dishes>> state;
        d.num = num.toInt();
        d.seat = seat.toInt();
        d.total = total.toDouble();
        d.state = state.toInt();
        return in;
    }
};
struct Report
{
    QString date;
    double turnover;
    double cost;
    double profit;
    int orderCount;
    operator QVariant() const
    {
    return QVariant::fromValue(*this);
    }
    inline friend QDataStream& operator<<(QDataStream& out, const Report& c)
    {
        out << c.date
            << QString::number(c.turnover)
            << QString::number(c.cost)
            << QString::number(c.profit)
            << QString::number(c.orderCount);
        return out;
    }
    inline friend  QDataStream& operator>>(QDataStream& in, Report & c)
    {
        QString turnover, cost, profit, orderCount;
        in >> c.date>> turnover >> cost>> profit>> orderCount;
        c.turnover = turnover.toDouble();
        c.cost = cost.toDouble();
        c.profit = profit.toDouble();
        c.orderCount = orderCount.toInt();
        return in;
    }
//    Report& operator=(const Report& other)
//    {
//        if (this != &other)
//        {
//            date = other.date;
//            turnover = other.turnover;
//            cost = other.cost;
//            profit = other.profit;
//            orderCount = other.orderCount;
//        }
//        return *this;
//    }
};
class Global {

public:
    static bool queryCurrentDayData(const QString table)
    {
        QSqlQuery query;
        QString queryT = QString("SELECT * FROM `%1` WHERE date = :date").arg(table);
        query.prepare(queryT);
        query.bindValue(":date", QDate::currentDate().toString("yyyy-MM-dd"));
        return (query.exec() && query.next());
    }
    static double currentDayCost()
    {
        double cost = 0;
        QSqlQuery query;
        QString queryT = QString("SELECT * FROM `daily_cost` WHERE date = :date");
        query.prepare(queryT);
        query.bindValue(":date", QDate::currentDate().toString("yyyy-MM-dd"));
        if(query.exec() && query.next())
        {
            cost = query.value(0).toDouble();
        }
        return cost;
    }
    static bool initReport()
    {
        QSqlQuery query;
        QString queryT = QString("insert into `%6`(%1,%2,%3,%4,%5) values(:%1,:%2,:%3,:%4,:%5)")
                .arg("date", "turnover", "cost", "profit", "orderCount", "daily_report");
        query.prepare(queryT);
        double cost = Global::currentDayCost();
        query.bindValue(":date", QDate::currentDate().toString("yyyy-MM-dd"));
        query.bindValue(":turnover", 0);
        query.bindValue(":cost", cost);
        query.bindValue(":profit", 0 - cost);
        query.bindValue(":orderCount", 0);
        return query.exec();
    }
    static Report dayReport(const QString &date)
    {
        Report report;
        QSqlQuery query;
        QString queryT = QString("SELECT * FROM `daily_report` WHERE date = :date");
        query.prepare(queryT);
        query.bindValue(":date", date);
        query.exec();
        while (query.next())
        {
            report.date = query.value(0).toString();
            report.turnover = query.value(1).toDouble();
            report.cost = query.value(2).toDouble();
            report.profit = query.value(3).toDouble();
            report.orderCount = query.value(4).toInt();
        }
        return report;
    }
};


Q_DECLARE_METATYPE(Dish);
Q_DECLARE_METATYPE(Class);
Q_DECLARE_METATYPE(Order);
Q_DECLARE_METATYPE(Report);
#endif
