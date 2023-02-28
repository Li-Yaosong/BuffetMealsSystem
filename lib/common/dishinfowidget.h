#ifndef DISHINFOWIDGET_H
#define DISHINFOWIDGET_H

#include <QWidget>
#include <QMap>
#include "libbms_global.h"
namespace Ui {
class DishInfoWidget;
}

class LIBBMS_EXPORT DishInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DishInfoWidget(QStringList list = {}, QWidget *parent = nullptr);
    ~DishInfoWidget();
    QMap<QString, QByteArray> info();
signals:
    void infoChanged(QMap<QString, QByteArray>);

private slots:
    void on_pushButton_browse_clicked();
    void textChanged();
private:
    void initStyle();
    Ui::DishInfoWidget *ui;
    QMap<QString, QByteArray> m_info;
};

#endif // DISHINFOWIDGET_H
