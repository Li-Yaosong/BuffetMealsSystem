#include "listwidget.h"
#include "ui_listwidget.h"
#include "stylesheet.h"
#include <QScrollBar>
class ListWidgetP
{
public:
    ListWidgetP(int head)
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
    void clear()
    {
        m_count = 0;
        m_dishWidgetList.clear();
    }
    int m_head;
    int m_count = 0;

private:
    QList<QWidget *> m_dishWidgetList;
};

ListWidget::ListWidget(int head, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListWidget),
    p(new ListWidgetP(head))
{
    ui->setupUi(this);
    switch (head) {
    case 0:
        ui->widget_head1->hide();
        ui->widget_head2->hide();
        ui->scrollArea_vertical->hide();
        break;
    case 1:
        ui->checkBox->hide();
        ui->widget_head2->hide();
        ui->scrollArea_grid->hide();
        break;
    case 2:
        ui->checkBox->hide();
        ui->widget_head1->hide();
        ui->scrollArea_grid->hide();
    default:
        break;
    }
    ui->scrollArea_grid->verticalScrollBar()->setStyleSheet(StyleSheet::scrollBarStyle());
}

ListWidget::~ListWidget()
{
    delete ui;
}

void ListWidget::addWidget(QWidget *widgit)
{
    switch (p->m_head) {
    case 0:
        ui->gridLayout->addWidget(widgit,p->m_count/4,p->m_count%4);
        break;
    default:
        ui->verticalLayout->insertWidget(ui->verticalLayout->count()- 1,widgit);
        break;
    }
    p->m_count++;
    p->saveDishWidget(widgit);
}

void ListWidget::clear()
{
    if(p->m_count != 0)
    {
        QList<QWidget *> list = p->dishList();
        for(QWidget *widgit : list)
        {
            ui->verticalLayout->removeWidget(widgit);
            widgit->deleteLater();
        }
        p->clear();
    }
}

void ListWidget::showTopCheckBox()
{
    if(p->m_head == 1)
    {
        ui->checkBox->show();
    }
}

void ListWidget::hideTopCheckBox()
{
    if(p->m_head)
    {
        ui->checkBox->hide();
    }
}
