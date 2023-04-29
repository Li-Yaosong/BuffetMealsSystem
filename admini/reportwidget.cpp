#include "reportwidget.h"
#include "qtablewidget.h"
#include "ui_reportwidget.h"
#include <QStandardItemModel>
class ReportWidgetPrivate
{
public:
    ReportWidgetPrivate()
        :m_model(new QStandardItemModel)
    {

    }
    ~ReportWidgetPrivate()
    {

    }
    QStandardItemModel *model()
    {
        QStandardItemModel *model = m_model;
        return model;
    }
private:
    QStandardItemModel *m_model;
};

ReportWidget::ReportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportWidget),
    p(new ReportWidgetPrivate)
{
    ui->setupUi(this);
    ui->tableView->setModel(p->model());
}

ReportWidget::~ReportWidget()
{
    delete ui;
}

void ReportWidget::addRowReport()
{

}
