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
    QStringList  header= {  QStringLiteral("日期"),
                            QStringLiteral("营业额"),
                            QStringLiteral("成本"),
                            QStringLiteral("利润"),
                            QStringLiteral("订单数")};
    p->model()->setHorizontalHeaderLabels(header);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->resizeColumnsToContents();
    /*
     * 只读
     */
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

ReportWidget::~ReportWidget()
{
    delete ui;
}

void ReportWidget::addRowReport()
{

}

void ReportWidget::initReport(QList<Report> list)
{
    p->model()->removeRows(0,p->model()->rowCount());
    p->model()->setRowCount(list.count());
    for(int i = 0; i < list.size(); i++)
    {
        p->model()->setData(p->model()->index(i,0),list.at(i).date);
        p->model()->setData(p->model()->index(i,1),list.at(i).turnover);
        p->model()->setData(p->model()->index(i,2),list.at(i).cost);
        p->model()->setData(p->model()->index(i,3),list.at(i).profit);
        p->model()->setData(p->model()->index(i,4),list.at(i).orderCount);
    }
}

