#include "classtabwidget.h"
#include "qtabbar.h"
#include "ui_classtabwidget.h"
class ClassTabWidgetP
{
public:
    ClassTabWidgetP()
    {

    }
    QMap<QString, QPair<int, DishListWidget *>> map;
};

ClassTabWidget::ClassTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassTabWidget),
    p(new ClassTabWidgetP)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();
}

ClassTabWidget::~ClassTabWidget()
{
    delete ui;
}

void ClassTabWidget::addTab(QPushButton *button, DishListWidget *widget,QString name)
{
    int count = ui->tabWidget->count();
    connect(button, &QPushButton::clicked, this, [this, count]{
//        int count = ui->tabWidget->count();
        ui->tabWidget->setCurrentIndex(count);
    });
    p->map.insert(name,QPair<int, DishListWidget *>(count,widget));
    ui->tabWidget->addTab(widget,name);
}

void ClassTabWidget::removeTab(QString name)
{
    if(p->map.value(name).second != nullptr)
    {
        ui->tabWidget->removeTab(p->map.value(name).first);
        p->map.value(name).second->deleteLater();
        p->map.remove(name);
    }
}

void ClassTabWidget::clear()
{
    ui->tabWidget->clear();
    for(QPair<int, DishListWidget *> pair : p->map.values())
    {
        pair.second->clear();
        pair.second->deleteLater();
    }
    p->map.clear();
}
