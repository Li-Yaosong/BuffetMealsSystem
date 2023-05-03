#include "service.h"
#include "QSqlDatabase"
#include "QDebug"
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
    db.setDatabaseName("bms");

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
    for(const QString &name : QSqlDatabase::drivers())
    {
        m_console->appendDebug(name);
    }
}

Service::~Service()
{
    delete m_console;
}

bool Service::accountVerification(const Account &account)
{
    Account request = getAccount(account.usr);
    qDebug()<<request.usr;
    qDebug()<<request.password;
    bool ret = request == account;
    qDebug()<< ret;
    return request == account;
}

bool Service::registerAccount(const Account &account)
{
    if(hasUsr(account.usr))
    {
        return false;
    }
    else
    {
        QSqlQuery query;
        query.prepare("insert into `account`(usr,password) values(:usr,:password)");
        query.bindValue(":usr", account.usr);
        query.bindValue(":password", account.password);
        return query.exec();
    }
}

bool Service::hasUsr(const QString &usr)
{
    QSqlQuery query;
    QString queryT = QString("SELECT * FROM `account` WHERE usr = :usr");
    query.prepare(queryT);
    query.bindValue(":usr", usr);
    return(query.exec() && query.next());
}

Account Service::getAccount(const QString &usr)
{
    Account account;
    QSqlQuery query;
    QString queryT = QString("SELECT * FROM `account` WHERE usr = :usr");
    query.prepare(queryT);
    query.bindValue(":usr", usr);
    if(query.exec() && query.next())
    {
        account.usr = query.value(0).toString();
        account.password = query.value(1).toString();

    }
    return account;
}

void Service::addClass(const Class &classInfo)
{
    QSqlQuery query;
    query.prepare("insert into `menu_classification`(class_name,image) values(:class_name,:image)");
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

void Service::modifiClass(const QString &newClass, const QString &old)
{
    QSqlQuery query;
    QString update = "update `menu_classification` SET `class_name` = :class_name WHERE `class_name` = :old";
    query.prepare(update);
    query.bindValue(":class_name", newClass);
    query.bindValue(":old", old);
    if(!query.exec())
    {
        m_console->appendDebug("update class error");
        qDebug() << "update class error";
        m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
        qDebug() << query.lastError().text().toLocal8Bit().data();
    }
    else
    {
        m_console->appendDebug("update class ok");
        qDebug() << "update class ok";
    }
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
    QString select = "select * from menu_classification";
    query.exec(select);
    while( query.next() )
    {
        map.insert(query.value(0).toString(), query.value(1).toByteArray());
    }
    return map;
}

QMap<QString, QList<Dish> > Service::getAllDishes()
{
    QMultiMap <QString, Dish> allmap;
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
        allmap.insert(dish.className,dish);
    }
    QMap<QString, QList<Dish>> reMap;
    QStringList keys = allmap.keys();
    for(const QString &key : qAsConst(keys))
    {
        reMap.insert(key, allmap.values(key));
    }
    return reMap;
}

QList<Report> Service::getDailyReport()
{
    QList<Report> list;
    QSqlQuery query;
    QString select = "select * from `daily_report`";
    query.exec(select);
    while( query.next() )
    {
        Report report;
        report.date = query.value(0).toString();
        report.turnover = query.value(1).toDouble();
        report.cost = query.value(2).toDouble();
        report.profit = query.value(3).toDouble();
        report.orderCount = query.value(4).toInt();
        list.append(report);
    }
    return list;
}

QList<Report> Service::getDailyReport(const QString &date)
{
    QList<Report> list;
    QSqlQuery query;
    QString select = "select * from `daily_report` where date = \"%1\"";
    query.exec(select.arg(date));
    while( query.next() )
    {
        Report report;
        report.date = query.value(0).toString();
        report.turnover = query.value(1).toDouble();
        report.cost = query.value(2).toDouble();
        report.profit = query.value(3).toDouble();
        report.orderCount = query.value(4).toInt();
        list.append(report);
    }
    return list;
}

QList<Report> Service::getMonthReport()
{
    QList<Report> list;
    QSqlQuery query;
    QString select = "select * from `monthly_report`";
    query.exec(select);
    while( query.next() )
    {
        Report report;
        report.date = query.value(0).toString();
        report.turnover = query.value(1).toDouble();
        report.cost = query.value(2).toDouble();
        report.profit = query.value(3).toDouble();
        report.orderCount = query.value(4).toInt();
        list.append(report);
    }
    return list;
}

QList<Report> Service::getMonthReport(const QString &date)
{
    QList<Report> list;
    QSqlQuery query;
    QString select = "select * from `monthly_report` where date = \"%1\"";
    query.exec(select.arg(date));
    while( query.next() )
    {
        Report report;
        report.date = query.value(0).toString();
        report.turnover = query.value(1).toDouble();
        report.cost = query.value(2).toDouble();
        report.profit = query.value(3).toDouble();
        report.orderCount = query.value(4).toInt();
        list.append(report);
    }
    return list;
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
        initReport();
    }
    else
    {
        m_console->appendDebug("insert daily_cost ok");
        qDebug() << "insert daily_cost ok";
    }
    QString month = QDateTime::fromString(date, "yyyy-MM-dd").toString("yyyy-MM");
    if(!Global::hasMonthCost(month))
    {
        setMonthlyCost(month, cost);
    }
    else
    {
        double currentMonthCost = Global::monthCost(month);
        updateMonthlyCost(month, currentMonthCost + cost);
    }
}

QList<QPair<QString, double>> Service::dailyCost()
{
    QList<QPair<QString, double>> list;
    QSqlQuery query;
    QString select = "select * from `daily_cost`";
    query.exec(select);
    while( query.next() )
    {
        QPair<QString, double> cost;
        cost.first = query.value(0).toString();
        cost.second = query.value(1).toDouble();
        list.append(cost);
    }
    return list;
}

void Service::setMonthlyCost(const QString date, const double cost)
{
    QSqlQuery query;
    query.prepare("insert into `monthly_cost`(date,cost) values(:date,:cost)");

    query.bindValue(":date", date);
    query.bindValue(":cost", cost);

    if(!query.exec())
    {
        m_console->appendDebug("insert error");
        qDebug() << "insert error";
        m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
        qDebug() << query.lastError().text().toLocal8Bit().data();
        initReport();
    }
    else
    {
        m_console->appendDebug("insert monthly_cost ok");
        qDebug() << "insert monthly_cost ok";
    }
}

void Service::updateMonthlyCost(const QString date, const double cost)
{
    QSqlQuery query;
    query.prepare("update `monthly_cost` set `cost` = :cost where `date` = :date");

    query.bindValue(":date", date);
    query.bindValue(":cost", cost);

    if(!query.exec())
    {
        m_console->appendDebug("insert error");
        qDebug() << "insert error";
        m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
        qDebug() << query.lastError().text().toLocal8Bit().data();
        initReport();
    }
    else
    {
        m_console->appendDebug("update monthly_cost ok");
        qDebug() << "update monthly_cost ok";
    }
}

void Service::initReport()
{
    if(Global::queryCurrentDayData("daily_report"))
    {
        m_console->appendDebug(QStringLiteral("今日报表已初始化"));
        qDebug() << QStringLiteral("今日报表已初始化");
    }
    else
    {
        if(Global::initReport())
        {
            m_console->appendDebug(QStringLiteral("今日报表已初始化成功！"));
            qDebug() << QStringLiteral("今日报表已初始化成功！");
            QList<Order> orderList = getOrder();
            for(const Order &order : orderList)
            {
                if(order.state == 2)
                {
                    updateReport(order.time, order.total);
                }
            }

        }
        else
        {
            m_console->appendDebug(QStringLiteral("今日报表初始化失败！"));
            qDebug() << QStringLiteral("今日报表初始化失败！");
        }
    }
}

void Service::updateReport(const QString &date, const double total)
{
    Report oldReport = Global::dayReport(date);
    qDebug()<<date;
    if(oldReport.date.isEmpty())
    {
        m_console->appendDebug(QStringLiteral("今日成本未设置，报表今日报表未初始化"));
        qDebug() << QStringLiteral("今日成本未设置，报表今日报表未初始化");
        return;
    }
    QSqlQuery query;
    QString update = "UPDATE `daily_report` SET `%1` = :%1, `%2` = :%2, `%3` = :%3 WHERE `%4` = :%4";
    query.prepare(update.arg("turnover", "profit","orderCount","date"));
    query.bindValue(":turnover", oldReport.turnover + total);
    query.bindValue(":profit", oldReport.turnover + total - oldReport.cost);
    query.bindValue(":orderCount", oldReport.orderCount + 1);
    query.bindValue(":date", oldReport.date);

    if(!query.exec())
    {
        m_console->appendDebug("update error");
        qDebug() << "update error";
        m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
        qDebug() << query.lastError().text().toLocal8Bit().data();
    }
    else
    {
        m_console->appendDebug("update daily report ok");
        qDebug() << "update daily report ok";
    }
    updateMonthReport(QDateTime::fromString(date, "yyyy-MM-dd").toString("yyyy-MM"), total);
}

void Service::updateMonthReport(const QString &date, const double total)
{
    Report oldReport = Global::monthReport(date);
    qDebug()<<date;
    if(oldReport.date.isEmpty())
    {
        m_console->appendDebug(QStringLiteral("本月成本未设置，本月报表未初始化"));
        qDebug() << QStringLiteral("本月成本未设置，本月报表未初始化");
        return;
    }
    QSqlQuery query;
    QString update = "UPDATE `monthly_report` SET `%1` = :%1, `%2` = :%2, `%3` = :%3 WHERE `%4` = :%4";
    query.prepare(update.arg("turnover", "profit","orderCount","date"));
    query.bindValue(":turnover", oldReport.turnover + total);
    query.bindValue(":profit", oldReport.turnover + total - oldReport.cost);
    query.bindValue(":orderCount", oldReport.orderCount + 1);
    query.bindValue(":date", oldReport.date);

    if(!query.exec())
    {
        m_console->appendDebug("update error");
        qDebug() << "update error";
        m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
        qDebug() << query.lastError().text().toLocal8Bit().data();
    }
    else
    {
        m_console->appendDebug("update monthly report ok");
        qDebug() << "update monthly report ok";
    }
}

void Service::updateReportWithoutNew(const QString &date, const double total, const int orderCount, const QString &tab)
{
    QSqlQuery query;
    QString update = "UPDATE `%6` SET `%1` = :%1, `%2` = :%2, `%3` = :%3, `%4` = :%4 WHERE `%5` = :%5";
    query.prepare(update.arg("turnover", "cost", "profit","orderCount","date",tab));
    query.bindValue(":turnover", total);
    double cost = 0;
    if(tab == "daily_report")
    {
        if(Global::hasDayCost(date))
        {
            cost = Global::dayCost(date);
        }
    }
    else
    {
        if(Global::hasMonthCost(date))
        {
            cost = Global::monthCost(date);
        }
    }
    query.bindValue(":cost",cost);
    query.bindValue(":profit", total - cost);
    query.bindValue(":orderCount", orderCount);
    query.bindValue(":date", date);

    if(!query.exec())
    {
        m_console->appendDebug("update error");
        qDebug() << "update error";
        m_console->appendDebug(query.lastError().text().toLocal8Bit().data());
        qDebug() << query.lastError().text().toLocal8Bit().data();
    }
    else
    {
        m_console->appendDebug("update report ok");
        qDebug() << "update order ok";
    }
}

double Service::calculateTotal(QList<double> doubleList)
{
    double allTotal = 0;
    for(const double total : qAsConst(doubleList))
    {
        allTotal += total;
    }
    return allTotal;
}

void Service::organizeData()
{
    //组织每月成本
    organizeMouthCost();
    //组织报表
    QList<Order> allOrderList = getOrder();
    organizeDailyReport(allOrderList);
    //组织每月报表
    QList<Report> allDayReport = getDailyReport();
    organizeMouthReport(allDayReport);
}

void Service::organizeMouthCost()
{
    QList<QPair<QString, double>> alldailyCost = dailyCost();
    QMultiMap<QString, double> monthDailyCost;
    for(const QPair<QString, double> &cost : qAsConst(alldailyCost))
    {
        QString month = QDateTime::fromString(cost.first, "yyyy-MM-dd").toString("yyyy-MM");
        monthDailyCost.insert(month, cost.second);
    }
    QStringList monthList = monthDailyCost.keys();
    for(const QString &month : qAsConst(monthList))
    {
        double allCost = calculateTotal(monthDailyCost.values(month));

        if(!Global::hasMonthCost(month))
        {
            setMonthlyCost(month, allCost);
        }
        else
        {
            updateMonthlyCost(month, allCost);
        }
    }
}

void Service::organizeDailyReport(const QList<Order> &allOrder)
{
    //组织每日报表
    QMultiMap<QString, double> dailyIncome;
    for(const Order &order : qAsConst(allOrder))
    {
        if(order.state == 2)
        {
            QString day = QDateTime::fromString(order.time,"yyyy-MM-ddThh:mm:ss.zzz").toString("yyyy-MM-dd");
            dailyIncome.insert(day,order.total);
        }
        QStringList dayList = dailyIncome.keys();
        for(const QString &day : qAsConst(dayList))
        {
            double allTotal = calculateTotal(dailyIncome.values(day));

            if(!Global::hasdayReport(day))
            {
                Global::initReport(day);
                updateReportWithoutNew(day, allTotal, dailyIncome.values(day).count());
            }
            else
            {
                updateReportWithoutNew(day, allTotal,dailyIncome.values(day).count());
            }
        }
    }
}

void Service::organizeMouthReport(const QList<Report> &allDayReport)
{
    QMultiMap<QString, double> monthlyIncome;
    QMultiMap<QString, double> monthlyOrder;
    for(const Report &report : qAsConst(allDayReport))
    {
        QString month = QDateTime::fromString(report.date,"yyyy-MM-dd").toString("yyyy-MM");
        monthlyIncome.insert(month,report.turnover);
        monthlyOrder.insert(month, double(report.orderCount));
        QStringList monthList = monthlyIncome.keys();
        for(const QString &m : qAsConst(monthList))
        {
            double allTotal = calculateTotal(monthlyIncome.values(m));
            int allOrder = int(calculateTotal(monthlyOrder.values(m)));
            if(!Global::hasMonthReport(m))
            {
                Global::initReport(m,"monthly_report");
                updateReportWithoutNew(m, allTotal,allOrder,"monthly_report");

            }
            else
            {
                updateReportWithoutNew(m, allTotal, allOrder,"monthly_report");
            }
        }
    }
}


