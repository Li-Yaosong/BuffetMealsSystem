#ifndef DISHWIDGET_H
#define DISHWIDGET_H

#include <QWidget>
#include <QVariant>
namespace Ui {
class DishWidget;
}
class DishesEdict;
class DishWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DishWidget(QWidget *parent = nullptr, QMap<QString, QVariant> data ={});
    ~DishWidget();
    void setClass(const QString &num);
    void setName(const QString &name);
    void setPrice(const double &price);
    void setStorage(const QString &storage);
    void showCheckBox();
    void hideCheckBox();
private slots:
    void on_pushButton_clicked();
signals:
    void checkBoxStateChanged(QString name, bool del);

private:
    Ui::DishWidget *ui;
    DishesEdict *m_imageW;
};

#endif // DISHWIDGET_H
