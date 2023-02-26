#ifndef WIDGET_H
#define WIDGET_H

#include "rep_service_source.h"
#include <QObject>
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
    void addClass(const QMap<QString, QByteArray> &map);
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
    void addDishes(const QMap<QString, QByteArray> &map);
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
     * \brief getAllClass
     * 获取全部类别
     * \return 全部类别
     */
    QByteArray getAllClass();
    /*!
     * \brief getAllDishes
     * 获取全部菜单
     * \return 全部菜单
     */
    QByteArray getAllDishes();
private:
    Console *m_console;
};
#endif // WIDGET_H
