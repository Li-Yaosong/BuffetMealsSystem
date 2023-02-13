#ifndef WIDGET_H
#define WIDGET_H

#include "rep_service_source.h"
#include <QObject>
QT_BEGIN_NAMESPACE
namespace Ui { class Service; }
QT_END_NAMESPACE

class Service : public ServiceSimpleSource
{
    Q_OBJECT
public:
    Service(QObject* parent = nullptr);
    ~Service();
    void addDishes(const QMap<QString, QByteArray> &map);
    QByteArray getAllDishes();
    QByteArray showImage();
};
#endif // WIDGET_H
