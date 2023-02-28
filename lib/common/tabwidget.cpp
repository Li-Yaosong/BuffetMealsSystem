#include "tabwidget.h"
#include "qtabbar.h"
#include "ui_tabwidget.h"
class TabWidgetP
{
public:
    TabWidgetP()
    {

    }
    QMap<QString, QPair<int, ListWidget *>> map;
};

TabWidget::TabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabWidget),
    p(new TabWidgetP)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();
}

TabWidget::~TabWidget()
{
    delete ui;
}

void TabWidget::addTab(QPushButton *button, ListWidget *widget,QString name)
{
    int count = ui->tabWidget->count();
    connect(button, &QPushButton::clicked, this, [this, count]{
//        int count = ui->tabWidget->count();
        ui->tabWidget->setCurrentIndex(count);
    });
    p->map.insert(name,QPair<int, ListWidget *>(count,widget));
    ui->tabWidget->addTab(widget,name);
}

void TabWidget::removeTab(QString name)
{
    if(p->map.value(name).second != nullptr)
    {
        ui->tabWidget->removeTab(p->map.value(name).first);
        p->map.value(name).second->deleteLater();
        p->map.remove(name);
    }
}

void TabWidget::clear()
{
    ui->tabWidget->clear();
    for(QPair<int, ListWidget *> pair : p->map.values())
    {
        pair.second->clear();
        pair.second->deleteLater();
    }
    p->map.clear();
}
