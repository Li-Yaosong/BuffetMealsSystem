/* ************************************************************************************************
 * class Name : Service
 *
 * describe:
 * 数据库增删改查服务类
 *
 * function:
 * void addClass(const QMap<QString, QByteArray> &)     -- 添加类别
 * void delClass(const QStringList &)                   -- 删除类别
 * void addDishes(const QMap<QString, QByteArray> &)    -- 添加菜单
 * void delDishes(const QStringList &)                  -- 删除菜单
 * void addOrder(const QMap<QString, QByteArray> &)     -- 新增订单
 * QByteArray getAllClass()                             -- 获取全部类别
 * QByteArray getAllDishes()                            -- 获取全部菜单
 *
 * Create Time : 2023-02-28 18:04:30
 * By liyaosong
 **************************************************************************************************/
#ifndef WIDGET_H
#define WIDGET_H

#include "rep_service_source.h"
#include <QObject>
#include "global.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Service; }
QT_END_NAMESPACE
class Console;
class Service : public ServiceSimpleSource
{
    Q_OBJECT
public:
    Service(QObject* parent = nullptr);
    ~Service();
    /*!
     * \brief addClass
     * 添加类别
     * \param map
     */
    void addClass(const Class &classInfo);
    /*!
     * \brief delClass
     * 删除类别
     * \param delList 类别名列表
     */
    void delClass(const QStringList &delList);
    /*!
     * \brief addDishes
     * 添加菜品
     * \param map 菜品信息
     */
    void addDishes(const Dish &dishInfo);
    /*!
     * \brief modifiDishe
     * 修改菜单
     * \param dishInfo
     * \param old
     */
    void modifiDishe(const Dish &dishInfo, const QString &old);
    /*!
     * \brief delDishes
     * 删除菜品
     * \param delList 菜品名列表
     */
    void delDishes(const QStringList &delList);
    /*!
     * \brief addOrder
     * 插入订单
     * \param map 订单信息
     */
    void addOrder(const QMap<QString, QByteArray> &map);
    /*!
     * \brief getOrder
     * 获取订单
     * \return
     */
    QList<Order> getOrder();
    /*!
     * \brief getAllClass
     * 获取全部类别
     * \return 全部类别
     */
    void updateOrder(int num, int state);
    QMap<QString, QVariant> getAllClass();
    /*!
     * \brief getAllDishes
     * 获取全部菜单
     * \return 全部菜单
     */
    QMap<QString, QList<Dish>> getAllDishes();
    /*!
     * \brief setDailyCost
     * 设置当天成本
     * \param date 日期
     * \param cost 成本
     */
    void setDailyCost(const QString date, const double cost);
private:
    Console *m_console;
};
#endif // WIDGET_H
