#ifndef DISHINFOWIDGET_H
#define DISHINFOWIDGET_H

#include <QWidget>

namespace Ui {
class DishInfoWidget;
}

class DishInfoWidget : public QWidget
{


    Q_OBJECT

public:
    struct DishInfo{
        QString name;
        double price;
        QString imagePath;
        QString storage = "yes";
    };
    explicit DishInfoWidget(QWidget *parent = nullptr);
    ~DishInfoWidget();
    DishInfo info();
signals:
    void infoChanged();

private slots:
    void on_pushButton_browse_clicked();

private:
    Ui::DishInfoWidget *ui;
};

#endif // DISHINFOWIDGET_H
