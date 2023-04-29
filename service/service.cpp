#include "service.h"
#include "QSqlDatabase"
#include "QDebug"
#include <QFileDialog>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>
#include <QList>
#include <QMultiMap>
#include "console.h"
Service::Service(QObject *parent)
    : ServiceSimpleSource(parent),
      m_console(new Console)
{
    m_console->show();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    /*
     * 连接远程mysql
     * host     : 'sql.lys-kd.com'
     * user     : 'liyaosong'
     * password : '20201110Kd'
     * database : 'ordering_system'
     */
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("ordering_system");

    if(db.open())
    {
        /*
         * 数据库连接成功
         */
        m_console->appendDebug(tr("Database connection successful!"));
    }
    else
    {
        /*
         * 数据库连接失败
         */
        m_console->appendDebug(tr("Database connection failure!"));
    }
//    for(const QString &name : QSqlDatabase::drivers())
//    {
//        m_console->appendDebug(name);
//    }
}

Service::~Service()
{
    delete m_console;
}

void Service::addClass(const Class &classInfo)
{
    QSqlQuery query;
    query.prepare("insert into menu_classification(class_name,image) values(:class_name,:image)");
    query.bindValue(":class_name", classInfo.name);
    query.bindValue(":image", classInfo.image);
    if(!query.exec())
        {
            m_console->appendDebug("insert error");
            qDebug() << "insert error";
            m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
            qDebug() << query.lastError().text().toLocal8Bit().data();
        }
        else
        {
            qDebug() << "insert class ok";
    }
}

void Service::delClass(const QStringList &delList)
{
    QSqlQuery query;
    for(const QString &name : delList)
    {
        query.prepare(QString("delete from menu where class='%1'").arg(name));
        if(!query.exec())
        {
            m_console->appendDebug("del error");
            qDebug() << "del error";
            m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
            qDebug() << query.lastError().text().toLocal8Bit().data();
        }
        else
        {
            m_console->appendDebug("del ok");
            qDebug() << "del ok";
        }
        query.prepare(QString("delete from menu_classification where class_name='%1'").arg(name));
        if(!query.exec())
        {
            m_console->appendDebug("del error");
            qDebug() << "del error";
            m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
            qDebug() << query.lastError().text().toLocal8Bit().data();
        }
        else
        {
            m_console->appendDebug("del class ok");
            qDebug() << "del class ok";
        }
    }
}

void Service::addDishes(const Dish &dishInfo)
{
    QSqlQuery query;
    query.prepare("insert into menu(name,class,price,image,storage) values(:name,:class,:price,:image,:storage)");
    query.bindValue(":name", dishInfo.name);
    query.bindValue(":class", dishInfo.className);
    query.bindValue(":price", dishInfo.price);
    query.bindValue(":image", dishInfo.image);
    query.bindValue(":storage", dishInfo.storage);

    if(!query.exec())
    {
        m_console->appendDebug("insert error");
        qDebug() << "insert error";
        m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
        qDebug() << query.lastError().text().toLocal8Bit().data();
    }
    else
    {
        m_console->appendDebug("insert dishes ok");
        qDebug() << "insert dishes ok";
    }
}

void Service::modifiDishe(const Dish &dishInfo, const QString &old)
{
    delDishes({old});
    addDishes(dishInfo);
}

void Service::delDishes(const QStringList &delList)
{
    QSqlQuery query;
    for(const QString &name : delList)
    {
        query.prepare(QString("delete from menu where name='%1'").arg(name));
        if(!query.exec())
        {
            m_console->appendDebug("del error");
            qDebug() << "del error";
            m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
            qDebug() << query.lastError().text().toLocal8Bit().data();
        }
        else
        {
            m_console->appendDebug("del ok");
            qDebug() << "del ok";
        }
    }

}

void Service::addOrder(const QMap<QString, QByteArray> &map)
{
    QSqlQuery query;
    query.prepare("insert into `order`(num,seat,time,total,dishes,state) values(NULL,:seat,NOW(),:total,:dishes,:state)");
    QDateTime dateTime(QDateTime::currentDateTime());
    QStringList keyList = map.keys();
    for(const QString &key : keyList)
    {
        if(key == "seat" || key == "state")
        {
            query.bindValue(":" + key, map.value(key).toInt());
        }
        else if(key == "total")
        {
            query.bindValue(":" + key, map.value(key).toDouble());
        }
        else
        {
            query.bindValue(":" + key, map.value(key));
        }
    }
//    query.bindValue(":time",dateTime.toString("yyyy-MM-dd hh:mm:ss"));
    if(!query.exec())
    {
        m_console->appendDebug("insert error");
        qDebug() << "insert error";
        m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
        qDebug() << query.lastError().text().toLocal8Bit().data();
    }
    else
    {
        m_console->appendDebug("insert order ok");
        qDebug() << "insert order ok";
    }
}

QList<Order> Service::getOrder()
{
    QList<Order> list;
    QSqlQuery query;
    QString select = "select * from `order`";
    query.exec(select);
    while( query.next() )
    {
        Order order;
        order.num = query.value(0).toInt();
        order.seat = query.value(1).toInt();
        order.time = query.value(2).toString();
        order.total = query.value(3).toDouble();
        order.dishes = query.value(4).toByteArray();
        order.state = query.value(5).toInt();
        list.append(order);
    }
    return list;
}

void Service::updateOrder(int num, int state)
{
    QSqlQuery query;
    QString update = "UPDATE `order` SET `state` = :value WHERE `num` = :num";
    query.prepare(update);
    query.bindValue(":value", state);
    query.bindValue(":num", num);
    if(!query.exec())
    {
        m_console->appendDebug("update error");
        qDebug() << "update error";
        m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
        qDebug() << query.lastError().text().toLocal8Bit().data();
    }
    else
    {
        m_console->appendDebug("update order ok");
        qDebug() << "update order ok";
    }
}

QMap<QString, QVariant> Service::getAllClass()
{
    QMap<QString, QVariant> map;
    QSqlQuery query;
    QString select = "select * menu_classification";
    query.exec(select);
    while( query.next() )
    {
        map.insert(query.value(0).toString(), query.value(1).toByteArray());
    }
    return map;
}

QMap<QString, QList<Dish> > Service::getAllDishes()
{
    QMultiMap <QString, Dish>Allmap;
    QSqlQuery query;
    query.exec("select * from menu");

    while( query.next() )
    {
        Dish dish;
        dish.name = query.value(0).toString();
        dish.className = query.value(1).toString();
        dish.price = query.value(2).toDouble();
        dish.image = query.value(3).toByteArray();
        dish.storage = query.value(4).toInt();
        Allmap.insert(dish.className,dish);
    }
    QMap<QString, QList<Dish>> reMap;
    for(const QString &key : Allmap.keys())
    {
        reMap.insert(key, Allmap.values(key));
    }
    return reMap;
}

void Service::setDailyCost(const QString date, const double cost)
{
    QSqlQuery query;
    query.prepare("insert into `daily_cost`(date,cost) values(:date,:cost)");

    query.bindValue(":date", date);
    query.bindValue(":cost", cost);

    if(!query.exec())
    {
        m_console->appendDebug("insert error");
        qDebug() << "insert error";
        m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
        qDebug() << query.lastError().text().toLocal8Bit().data();
    }
    else
    {
        m_console->appendDebug("insert daily_cost ok");
        qDebug() << "insert daily_cost ok";
    }
}
