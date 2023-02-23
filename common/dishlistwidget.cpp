#include "dishlistwidget.h"
#include "ui_dishlistwidget.h"
class DishListWidgetP
{
public:
    DishListWidgetP(bool head)
        :m_head(head)
    {

    }
    void saveDishWidget(QWidget *widget)
    {
        m_dishWidgetList.append(widget);
    }
    QList<QWidget *> dishList()
    {
        return m_dishWidgetList;
    }
    bool m_head;
    int m_count = 0;

private:
    QList<QWidget *> m_dishWidgetList;
};

DishListWidget::DishListWidget(bool head, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DishListWidget),
    p(new DishListWidgetP(head))
{
    ui->setupUi(this);
    if(head)
    {
        ui->checkBox->hide();
        ui->scrollArea_grid->hide();
    }
    else
    {
        ui->widget_head->hide();
        ui->scrollArea_vertical->hide();
    }
}

DishListWidget::~DishListWidget()
{
    delete ui;
}

void DishListWidget::addDishWidget(QWidget *widgit)
{
    if(p->m_head)
    {
        ui->verticalLayout->insertWidget(ui->verticalLayout->count()- 1,widgit);
    }
    else
    {
        ui->gridLayout->addWidget(widgit,p->m_count/4,p->m_count%4);
        p->m_count++;
    }
    p->saveDishWidget(widgit);
}

void DishListWidget::clear()
{
    if(!p->dishList().isEmpty())
    {
        for(QWidget *widgit : p->dishList())
        {
            ui->verticalLayout->removeWidget(widgit);
            widgit->deleteLater();
        }
        p->dishList().clear();
    }
}

void DishListWidget::showTopCheckBox()
{
    if(p->m_head)
    {
        ui->checkBox->show();
    }
}

void DishListWidget::hideTopCheckBox()
{
    if(p->m_head)
    {
        ui->checkBox->hide();
    }
}
